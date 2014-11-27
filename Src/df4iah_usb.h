/*
 * df4iah_usb.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_USB_H_
#define DF4IAH_USB_H_


#include "chipdef.h"


void init_usb();
void close_usb();
void sendchar_usb(uint8_t data);
uint8_t recvchar_usb(void);
void recvBuffer_usb(pagebuf_t size);

#endif /* DF4IAH_USB_H_ */
