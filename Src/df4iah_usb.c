/*
 * df4iah_usb.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include "df4iah_usb.h"

#include <stdint.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <avr/wdt.h>
#include <util/delay.h>

#include "usbdrv/usbdrv.h"


extern uint8_t gBuffer[SPM_PAGESIZE];


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
void sendchar_usb(uint8_t data)
{
	// XXX TODO
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
void recvBuffer_usb(pagebuf_t size)
{
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? recvchar_usb() : 0xFF;
	}
}

// -- 8< --


#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	return 0;
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC uchar usbFunctionRead(uchar *data, uchar len)
{
	return 0xff;
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	return 1;
}

#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
USB_PUBLIC void usbFunctionWriteOut(uchar *data, uchar len)
{

}
