/*
 * df4iah_probe.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include <avr/wdt.h>
#include <util/delay.h>

#include "df4iah_probe.h"


#ifdef RELEASE
__attribute__((section(".df4iah_probe"), aligned(2)))
#endif
void init_probe()
{
	MCUCR &= ~(1<<PUD);								// PullUp Disable off

	PROBEDDR  &= ~(1<<PROBEPNUM);							// set probe line as input
	PROBEPORT |=  (1<<PROBEPNUM);							// and enable the pullup

	uint8_t dlyCnt = 250;
	while (--dlyCnt) {								// delay for reliable detection
        wdt_reset();
        _delay_ms(1);
    }
}

#ifdef RELEASE
__attribute__((section(".df4iah_probe"), aligned(2)))
#endif
void close_probe()
{
	PROBEPORT &= ~(1<<PROBEPNUM);							// clear PULLUP to default
}

#ifdef RELEASE
__attribute__((section(".df4iah_probe"), aligned(2)))
#endif
uint8_t check_jumper()
{
	if (PROBEPIN & (1<<PROBEPNUM)) {
		// pin is not grounded
		return 1;
	}
	return 0;
}
