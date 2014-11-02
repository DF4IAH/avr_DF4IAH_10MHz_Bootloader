/*
 * df4iah_usb.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include "df4iah_usb.h"

#include "usbdrv/usbdrv.h"


#ifdef RELEASE
__attribute__((section(".df4iah_usb"), aligned(2)))
#endif
void init_usb()
{
	usbInit();
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
