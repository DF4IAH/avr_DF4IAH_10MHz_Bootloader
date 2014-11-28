/*
 * df4iah_usb.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include <stdint.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <avr/wdt.h>
#include <util/delay.h>

#include "usbdrv/usbdrv.h"

#include "df4iah_usb.h"
#include "df4iah_usbAsp.h"
#include "df4iah_usbTpiDefs.h"
#include "df4iah_usbIsp.h"


extern uint8_t gBuffer[SPM_PAGESIZE];


static uchar replyBuffer[8];

static uchar prog_state = PROG_STATE_IDLE;
static uchar prog_sck = USBASP_ISP_SCK_AUTO;

static uchar prog_address_newmode = 0;
static unsigned long prog_address;
static unsigned int prog_nbytes = 0;
static unsigned int prog_pagesize;
static uchar prog_blockflags;
static uchar prog_pagecounter;


#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void init_usb()
{
	usbInit();
	USB_INTR_ENABLE &= ~(_BV(USB_INTR_ENABLE_BIT));
	usbDeviceDisconnect();			/* enforce re-enumeration, do this while interrupts are disabled! */

    uint8_t i = 250;
    while (--i) {					/* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }

    usbDeviceConnect();
	USB_INTR_ENABLE |= _BV(USB_INTR_ENABLE_BIT);
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void close_usb()
{
	USB_INTR_ENABLE &= ~(_BV(USB_INTR_ENABLE_BIT));
	usbDeviceDisconnect();
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
uint8_t recvchar_usb(void)
{
	return 0;  // XXX TODO
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void sendchar_usb(uint8_t data)
{
	// XXX TODO
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void recvBuffer_usb(uint16_t addr, uint8_t* dptr, uint8_t len)
{
#if 0
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? recvchar_usb() : 0xFF;
	}
#else
#endif
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void sendBuffer_usb(uint16_t addr, const uint8_t* sptr, uint8_t len)
{
}

// -- 8< --


#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	uchar len = 0;

	if (data[1] == USBASP_FUNC_CONNECT) {

#if 0
		/* set SCK speed */
#ifdef SLOW_SERIAL_CLOCK_SELECTION
		if ((PINC & (1 << PC2)) == 0) {
			ispSetSCKOption(USBASP_ISP_SCK_8);
		} else {
#endif
			ispSetSCKOption(prog_sck);
#ifdef SLOW_SERIAL_CLOCK_SELECTION
		}
#endif
#else
#endif

		/* set compatibility mode of address delivering */
		prog_address_newmode = 0;

#if 0
		ledRedOn();
		ispConnect();
#endif

	} else if (data[1] == USBASP_FUNC_DISCONNECT) {
#if 0
		ispDisconnect();
		ledRedOff();
#else
#endif

	} else if (data[1] == USBASP_FUNC_TRANSMIT) {
#if 0
		replyBuffer[0] = ispTransmit(data[2]);
		replyBuffer[1] = ispTransmit(data[3]);
		replyBuffer[2] = ispTransmit(data[4]);
		replyBuffer[3] = ispTransmit(data[5]);
#else
#endif
		len = 4;

	} else if (data[1] == USBASP_FUNC_READFLASH) {
		if (!prog_address_newmode) {
			prog_address = (data[3] << 8) | data[2];
		}

		prog_nbytes = (data[7] << 8) | data[6];
		prog_state = PROG_STATE_READFLASH;
		len = 0xff; /* multiple in */

	} else if (data[1] == USBASP_FUNC_READEEPROM) {
		if (!prog_address_newmode) {
			prog_address = (data[3] << 8) | data[2];
		}

		prog_nbytes = (data[7] << 8) | data[6];
		prog_state = PROG_STATE_READEEPROM;
		len = 0xff; /* multiple in */

	} else if (data[1] == USBASP_FUNC_ENABLEPROG) {
#if 0
		replyBuffer[0] = ispEnterProgrammingMode();
#else
#endif
		len = 1;

	} else if (data[1] == USBASP_FUNC_WRITEFLASH) {
		if (!prog_address_newmode) {
			prog_address = (data[3] << 8) | data[2];
		}

		prog_pagesize = data[4];
		prog_blockflags = data[5] & 0x0F;
		prog_pagesize |= (((unsigned int) data[5] & 0xF0) << 4);
		if (prog_blockflags & PROG_BLOCKFLAG_FIRST) {
			prog_pagecounter = prog_pagesize;
		}

		prog_nbytes = (data[7] << 8) | data[6];
		prog_state = PROG_STATE_WRITEFLASH;
		len = 0xff; /* multiple out */

	} else if (data[1] == USBASP_FUNC_WRITEEEPROM) {
		if (!prog_address_newmode) {
			prog_address = (data[3] << 8) | data[2];
		}

		prog_pagesize = 0;
		prog_blockflags = 0;
		prog_nbytes = (data[7] << 8) | data[6];
		prog_state = PROG_STATE_WRITEEEPROM;
		len = 0xff; /* multiple out */

	} else if (data[1] == USBASP_FUNC_SETLONGADDRESS) {
		/* set new mode of address delivering (ignore address delivered in commands) */
		prog_address_newmode = 1;
		/* set new address */
		prog_address = *((unsigned long*) &data[2]);

	} else if (data[1] == USBASP_FUNC_SETISPSCK) {
		/* set sck option */
		prog_sck = data[2];
		replyBuffer[0] = 0;
		len = 1;

	} else if (data[1] == USBASP_FUNC_TPI_CONNECT) {
#if 0
		tpi_dly_cnt = data[2] | (data[3] << 8);

		/* RST high */
		ISP_OUT |= (1 << ISP_RST);
		ISP_DDR |= (1 << ISP_RST);

		clockWait(3);

		/* RST low */
		ISP_OUT &= ~(1 << ISP_RST);
		ledRedOn();

		clockWait(16);
		tpi_init();
#else
#endif

	} else if (data[1] == USBASP_FUNC_TPI_DISCONNECT) {
#if 0
		tpi_send_byte(TPI_OP_SSTCS(TPISR));
		tpi_send_byte(0);

		clockWait(10);

		/* pulse RST */
		ISP_OUT |= (1 << ISP_RST);
		clockWait(5);
		ISP_OUT &= ~(1 << ISP_RST);
		clockWait(5);

		/* set all ISP pins inputs */
		ISP_DDR &= ~((1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI));
		/* switch pullups off */
		ISP_OUT &= ~((1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI));

		ledRedOff();
#else
#endif

	} else if (data[1] == USBASP_FUNC_TPI_RAWREAD) {
#if 0
		replyBuffer[0] = tpi_recv_byte();
#else
#endif
		len = 1;

	} else if (data[1] == USBASP_FUNC_TPI_RAWWRITE) {
#if 0
		tpi_send_byte(data[2]);
#else
#endif

	} else if (data[1] == USBASP_FUNC_TPI_READBLOCK) {
#if 0
		prog_address = (data[3] << 8) | data[2];
		prog_nbytes = (data[7] << 8) | data[6];
		prog_state = PROG_STATE_TPI_READ;
#else
#endif
		len = 0xff; /* multiple in */

	} else if (data[1] == USBASP_FUNC_TPI_WRITEBLOCK) {
#if 0
		prog_address = (data[3] << 8) | data[2];
		prog_nbytes = (data[7] << 8) | data[6];
		prog_state = PROG_STATE_TPI_WRITE;
#else
#endif
		len = 0xff; /* multiple out */

	} else if (data[1] == USBASP_FUNC_GETCAPABILITIES) {
		replyBuffer[0] = USBASP_CAP_0_LOC;
		replyBuffer[1] = 0;
		replyBuffer[2] = 0;
		replyBuffer[3] = 0;
		len = 4;
	}

	usbMsgPtr = (usbMsgPtr_t) replyBuffer;

	return len;
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC uchar usbFunctionRead(uchar *data, uchar len)
{
	uchar i;

	/* check if programmer is in correct read state */
	if ((prog_state != PROG_STATE_READFLASH) &&
		(prog_state	!= PROG_STATE_READEEPROM) &&
		(prog_state != PROG_STATE_TPI_READ)) {
		return 0xff;
	}

	/* fill packet TPI mode */
	if (prog_state == PROG_STATE_TPI_READ) {
#if 0
		tpi_read_block(prog_address, data, len);
#else
#endif
		prog_address += len;
		return len;
	}

	/* fill packet ISP mode */
	for (i = 0; i < len; i++) {
		if (prog_state == PROG_STATE_READFLASH) {
#if 0
			data[i] = ispReadFlash(prog_address);
#else
#endif
		} else {
#if 0
			data[i] = ispReadEEPROM(prog_address);
#else
#endif
		}
		prog_address++;
	}

	/* last packet? */
	if (len < 8) {
		prog_state = PROG_STATE_IDLE;
	}

	return len;
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	uchar retVal = 0;
	uchar i;

	/* check if programmer is in correct write state */
	if ((prog_state != PROG_STATE_WRITEFLASH) &&
		(prog_state	!= PROG_STATE_WRITEEEPROM) &&
		(prog_state != PROG_STATE_TPI_WRITE)) {
		return 0xff;
	}

	if (prog_state == PROG_STATE_TPI_WRITE) {
#if 0
		tpi_write_block(prog_address, data, len);
#endif
		prog_address += len;
		prog_nbytes -= len;
		if (prog_nbytes <= 0) {
			prog_state = PROG_STATE_IDLE;
			return 1;
		}
		return 0;
	}

	for (i = 0; i < len; i++) {
		if (prog_state == PROG_STATE_WRITEFLASH) {
			/* Flash */

			if (prog_pagesize == 0) {
				/* not paged */
#if 0
				ispWriteFlash(prog_address, data[i], 1);
#else
#endif
			} else {
				/* paged */
#if 0
				ispWriteFlash(prog_address, data[i], 0);
#else
#endif
				prog_pagecounter--;
				if (prog_pagecounter == 0) {
#if 0
					ispFlushPage(prog_address, data[i]);
#else
#endif
					prog_pagecounter = prog_pagesize;
				}
			}

		} else {
			/* EEPROM */
			ispWriteEEPROM(prog_address, data[i]);
		}

		prog_nbytes--;

		if (prog_nbytes == 0) {
			prog_state = PROG_STATE_IDLE;
			if ((prog_blockflags & PROG_BLOCKFLAG_LAST) &&
				(prog_pagecounter != prog_pagesize)) {
#if 0
				/* last block and page flush pending, so flush it now */
				ispFlushPage(prog_address, data[i]);
#else
#endif
			}
			retVal = 1; // Need to return 1 when no more data is to be received
		}

		prog_address++;
	}

	return retVal;
}

#if USB_CFG_IMPLEMENT_FN_WRITEOUT
# ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
# endif
USB_PUBLIC void usbFunctionWriteOut(uchar *data, uchar len)
{

}
#endif
