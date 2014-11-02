/*
 * df4iah_usb.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include "df4iah_usb.h"

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <avr/wdt.h>
#include <util/delay.h>

#include "usbdrv/usbdrv.h"


#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void init_usb()
{
	usbInit();
    usbDeviceDisconnect();			/* enforce re-enumeration, do this while interrupts are disabled! */

    int i = 250;
    while (--i) {					/* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }

    usbDeviceConnect();
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
