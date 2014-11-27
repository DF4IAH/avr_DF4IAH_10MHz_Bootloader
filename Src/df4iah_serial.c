/*
 * df4iah_serial.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include <stdint.h>
#include <avr/interrupt.h>

#include "df4iah_serial.h"

#include "main.h"


extern uint8_t gBuffer[SPM_PAGESIZE];


#ifdef RELEASE
__attribute__((section(".df4iah_serial"), aligned(2)))
#endif
void init_serial()
{
	// set baud rate
	UART_BAUD_HIGH = ((UART_CALC_BAUDRATE(BAUDRATE)>>8) & 0xFF);
	UART_BAUD_LOW  = ( UART_CALC_BAUDRATE(BAUDRATE)     & 0xFF);

#ifdef UART_DOUBLESPEED
	UART_STATUS = (1<<UART_DOUBLE);
#endif

	UART_CTRL  = UART_CTRL_DATA;
	UART_CTRL2 = UART_CTRL2_DATA;
}

#ifdef RELEASE
__attribute__((section(".df4iah_serial"), aligned(2)))
#endif
void close_serial()
{
#ifdef UART_DOUBLESPEED
		UART_STATUS &= ~(_BV(UART_DOUBLE));
#endif
}

#ifdef RELEASE
__attribute__((section(".df4iah_serial"), aligned(2)))
#endif
void sendchar_serial(uint8_t data)
{
	while (!(UART_STATUS & _BV(UART_TXREADY)));
	UART_DATA = data;
}

#ifdef RELEASE
__attribute__((section(".df4iah_serial"), aligned(2)))
#endif
uint8_t recvchar_serial(void)
{
	while (!(UART_STATUS & _BV(UART_RXREADY)));
	return UART_DATA;
}

#ifdef RELEASE
__attribute__((section(".df4iah_serial"), aligned(2)))
#endif
void recvBuffer_serial(pagebuf_t size)
{
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? recvchar_serial() : 0xFF;
	}
}
