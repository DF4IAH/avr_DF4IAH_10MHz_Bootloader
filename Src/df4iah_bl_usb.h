/*
 * df4iah_usb.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_USB_H_
#define DF4IAH_USB_H_


#include "chipdef.h"
#include "usbdrv_bl/usbdrv.h"


void replyContent(uchar replyBuffer[], uchar data[]);

void init_usb();
void close_usb();

#endif /* DF4IAH_USB_H_ */
