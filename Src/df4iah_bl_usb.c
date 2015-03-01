/*
 * df4iah_bl_usb.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */
// tabsize: 4

#include <stdint.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <avr/wdt.h>
#include <avr/boot.h>
#include <util/delay.h>

#include "df4iah_bl_main.h"
#include "df4iah_bl_memory.h"
#include "df4iah_bl_usbAsp.h"

#include "df4iah_bl_usb.h"


#ifndef SIGRD
# define SIGRD 5
#endif


extern uint8_t mainIsJumperBlSet;
extern uint8_t mainStopAvr;

uchar replyBuffer[8];

uchar prog_connected = PROG_UNCONNECTED;
uchar prog_state = PROG_STATE_IDLE;

uchar prog_address_newmode = 0;
unsigned long prog_address;
unsigned int prog_nbytes = 0;
unsigned int prog_pagesize;
uchar prog_blockflags;
uchar prog_pagecounter;


#ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
#endif
void usb_bl_replyContent(uchar replyBuffer[], uchar data[])
{
	replyBuffer[0] = data[2];
	replyBuffer[1] = data[3];
	replyBuffer[2] = data[4];
	// replyBuffer[3] = 0;
}

#ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
#endif
void usb_bl_init()
{
	usbInit();
	USB_INTR_ENABLE &= ~(_BV(USB_INTR_ENABLE_BIT));
	usbDeviceDisconnect();			/* enforce re-enumeration, do this while interrupts are disabled! */

    uint8_t i = 250;
    while (--i) {											// fake USB disconnect for > 250 ms
        _delay_ms(1);
        wdt_reset();
    }

    usbDeviceConnect();
	USB_INTR_ENABLE |= _BV(USB_INTR_ENABLE_BIT);
}

#ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
#endif
void usb_bl_close()
{
	USB_INTR_ENABLE &= ~(_BV(USB_INTR_ENABLE_BIT));
	usbDeviceDisconnect();
}

/*  -- 8< -- */


#ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
#endif
USB_PUBLIC usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	const usbRequest_t* rq = (usbRequest_t*) data;
	uchar len = 0;

	if (rq->bRequest == USBASP_FUNC_CONNECT) {
		prog_connected = PROG_CONNECTED;

		/* set compatibility mode of address delivering */
		prog_address_newmode = 0;

	} else if (rq->bRequest == USBASP_FUNC_DISCONNECT) {
		prog_connected = PROG_UNCONNECTED;
		if (!mainIsJumperBlSet) {
			mainStopAvr = true;
		}

	} else if (rq->bRequest == USBASP_FUNC_TRANSMIT) {
		if ((rq->wValue.word == 0x0030) && (rq->wIndex.bytes[0] < 3)) {
			// signature bytes
			usb_bl_replyContent(replyBuffer, data);
			replyBuffer[3] = boot_signature_byte_get(data[4] << 1);
			len = 4;

		} else if (rq->wValue.word == 0x0050) {
			// lfuse bits - @see page 271f
			usb_bl_replyContent(replyBuffer, data);
			replyBuffer[3] = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
			len = 4;

		} else if (rq->wValue.word == 0x0858) {
			// hfuse bits
			usb_bl_replyContent(replyBuffer, data);
			replyBuffer[3] = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
			len = 4;

		} else if (rq->wValue.word == 0x0850) {
			// efuse bits
			usb_bl_replyContent(replyBuffer, data);
			replyBuffer[3] = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
			len = 4;

		} else if (rq->wValue.word == 0x0058) {
			// lock bits
			usb_bl_replyContent(replyBuffer, data);
			replyBuffer[3] = boot_lock_fuse_bits_get(GET_LOCK_BITS);
			len = 4;
		}

	} else if ((rq->bRequest == USBASP_FUNC_READFLASH) || (rq->bRequest == USBASP_FUNC_READEEPROM)) {
		if (prog_connected > PROG_UNCONNECTED) {
			if (!prog_address_newmode) {
				prog_address = rq->wValue.word;
			}

			prog_nbytes = rq->wLength.word;
			prog_state = (rq->bRequest == USBASP_FUNC_READFLASH) ?  PROG_STATE_READFLASH : PROG_STATE_READEEPROM;
			len = 0xff; /* multiple in */
		}

	} else if (rq->bRequest == USBASP_FUNC_ENABLEPROG) {
		if (prog_connected == PROG_CONNECTED) {
			prog_connected = PROG_PROGENABLED;
			replyBuffer[0] = 0;
		} else {
			replyBuffer[0] = 1;
		}
		len = 1;

	} else if ((rq->bRequest == USBASP_FUNC_WRITEFLASH) || (rq->bRequest == USBASP_FUNC_WRITEEEPROM)) {
		if (prog_connected == PROG_PROGENABLED) {
			if (!prog_address_newmode) {
				prog_address = rq->wValue.word;
			}

			if (rq->bRequest == USBASP_FUNC_WRITEFLASH) {
				prog_blockflags = data[5] & 0x0F;
				prog_pagesize |= (((unsigned int) data[5] & 0xF0) << 4) | data[4];
				if (prog_blockflags & PROG_BLOCKFLAG_FIRST) {
					prog_pagecounter = prog_pagesize;
				}
				prog_state = PROG_STATE_WRITEFLASH;

			} else {  /* data[1] == USBASP_FUNC_WRITEEEPROM */
				prog_pagesize = 0;
				prog_blockflags = 0;
				prog_state = PROG_STATE_WRITEEEPROM;
			}

			prog_nbytes = rq->wLength.word;
			len = 0xff; /* multiple out */
		}

	} else if (rq->bRequest == USBASP_FUNC_SETLONGADDRESS) {
		if (prog_connected > PROG_UNCONNECTED) {
			/* set new mode of address delivering (ignore address delivered in commands) */
			prog_address_newmode = 1;
			/* set new address */
			prog_address = rq->wValue.word;
		}

	} else if (rq->bRequest == USBASP_FUNC_SETISPSCK) {
		/* LOC does not implement that */
		replyBuffer[0] = 0;
		len = 1;

	} else if (rq->bRequest == USBASP_FUNC_TPI_CONNECT) {
		/* Tiny Programming Interface is not supported */

	} else if (rq->bRequest == USBASP_FUNC_TPI_DISCONNECT) {
		/* Tiny Programming Interface is not supported */

	} else if (rq->bRequest == USBASP_FUNC_TPI_RAWREAD) {
		/* Tiny Programming Interface is not supported */
		replyBuffer[0] = 0;
		len = 1;

	} else if (rq->bRequest == USBASP_FUNC_TPI_RAWWRITE) {
		/* Tiny Programming Interface is not supported */

	} else if (rq->bRequest == USBASP_FUNC_TPI_READBLOCK) {
		/* Tiny Programming Interface is not supported */
		len = 0xff; /* multiple in */

	} else if (rq->bRequest == USBASP_FUNC_TPI_WRITEBLOCK) {
		/* Tiny Programming Interface is not supported */
		len = 0xff; /* multiple out */

	} else if (rq->bRequest == USBASP_FUNC_GETCAPABILITIES) {
		/* Tiny Programming Interface is not supported */
		replyBuffer[3] = replyBuffer[2] = replyBuffer[1] = replyBuffer[0] = 0;  // USBASP_CAP_0_TPI;
		len = 4;
	}

	usbMsgPtr = (usbMsgPtr_t) replyBuffer;
	return len;
}

#ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
#endif
USB_PUBLIC uchar usbFunctionRead(uchar *data, uchar len)
{
	/* check if programmer is in correct read state */
	if ((prog_state != PROG_STATE_READFLASH) &&
		(prog_state	!= PROG_STATE_READEEPROM)) {
		return 0xff;
	}

	if (prog_state == PROG_STATE_READFLASH) {
		memory_bl_readFlashPage(data, len, prog_address);
	} else {
		memory_bl_readEEpromPage(data, len, prog_address);
	}
	prog_address += len;

	/* last packet? */
	if (len < 8) {
		prog_state = PROG_STATE_IDLE;
	}

	return len;
}

#ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
#endif
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	/* check if programmer is in correct write state */
	if ((prog_state != PROG_STATE_WRITEFLASH) &&
		(prog_state	!= PROG_STATE_WRITEEEPROM)) {
		return 0xff;
	}

	if (prog_state == PROG_STATE_WRITEFLASH) {
		memory_bl_writeFlashPage(data, len, prog_address);
	} else {
		memory_bl_writeEEpromPage(data, len, prog_address);
	}
	prog_address += len;

	prog_nbytes -= len;
	if (prog_nbytes <= 0) {
		prog_state = PROG_STATE_IDLE;
		return 1;
	}

	return 0;
}

#if USB_CFG_IMPLEMENT_FN_WRITEOUT
# ifdef RELEASE
__attribute__((section(".df4iah_bl_usb"), aligned(2)))
# endif
USB_PUBLIC void usbFunctionWriteOut(uchar *data, uchar len)
{

}
#endif
