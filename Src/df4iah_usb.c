/*
 * df4iah_usb.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include "df4iah_usb.h"

#include "usbdrv/usbdrv.h"


__attribute__((section(".df4iah_usb"), aligned(2)))
void init_usb()
{
	usbInit();
}


// -- 8< --


__attribute__((section(".df4iah_usb"), aligned(2)))
USB_PUBLIC usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	return 0;
}

__attribute__((section(".df4iah_usb"), aligned(2)))
USB_PUBLIC uchar usbFunctionRead(uchar *data, uchar len)
{
	return 0xff;
}

__attribute__((section(".df4iah_usb"), aligned(2)))
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	return 1;
}

__attribute__((section(".df4iah_usb"), aligned(2)))
USB_PUBLIC void usbFunctionWriteOut(uchar *data, uchar len)
{

}
