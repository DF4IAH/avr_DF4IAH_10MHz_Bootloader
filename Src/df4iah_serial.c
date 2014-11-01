/*
 * df4iah_serial.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "df4iah_serial.h"

#include "main.h"


extern uint8_t gBuffer[SPM_PAGESIZE];


void sendchar(uint8_t data)
{
	while (!(UART_STATUS & (1<<UART_TXREADY)));
	UART_DATA = data;
}

uint8_t recvchar(void)
{
	while (!(UART_STATUS & (1<<UART_RXREADY)));
	return UART_DATA;
}

void recvBuffer(pagebuf_t size)
{
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? recvchar() : 0xFF;
	}
}

// --

void send_boot(void)
{
	/*
	sendchar('A');
	sendchar('V');
	sendchar('R');
	sendchar('B');
	sendchar('O');
	sendchar('O');
	sendchar('T');
	*/

	sendchar('F');
	sendchar('D');
	sendchar('L');
	sendchar(' ');
	sendchar('v');
	sendchar(VERSION_HIGH);
	sendchar(VERSION_LOW);
}

void ser_error_msg()
{
	sendchar('*');
	sendchar('E');
	sendchar('R');
	sendchar('R');
	sendchar('-');
	sendchar('9');
	sendchar('9');
	sendchar('*');

	cli();
	sleep_cpu();
}
