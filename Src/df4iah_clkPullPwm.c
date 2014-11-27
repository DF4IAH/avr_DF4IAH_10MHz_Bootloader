/*
 * df4iah_clkPullPwm.c
 *
 *  Created on: 24.11.2014
 *      Author: espero
 */


#include <avr/io.h>

#include "chipdef.h"
#include "df4iah_clkPullPwm.h"


#define DEFAULT_PWM_COUNT  0x8000


#ifdef RELEASE
__attribute__((section(".df4iah_clkpullpwm"), aligned(2)))
#endif
void init_clkPullPwm()
{
	// set the timer-1 counter to zero.
	TCNT1L = TCNT1H = 0x00;

	// use the ICR1 register as TOP=0xffff value for the PWM-A output.
	ICR1L = ICR1H = 0xff;

	// set the timer-1 PWM-A compare register - high byte first
	OCR1AH = (DEFAULT_PWM_COUNT >> 8);
	OCR1AL = (DEFAULT_PWM_COUNT & 0xff);

	// set the timer-1 mode of operation: 0xe = Fast PWM, counting up, TOP := ICR1 [. . WGM11 WGM10]
	// set the timer-1 compare-A waveform generator to: PWM, 1 at >= match, 0 else
	TCCR1A = (0b10<<COM1A0) | (0b10<<WGM10);

	// set the timer-1 mode of operation: 0xe = Fast PWM, counting up, TOP := ICR1 [WGM13 WGM12 . .]
	// set the timer-1 clock source to 20 MHz XTAL.
	TCCR1B = (0b11<<WGM12) | (0b001<<CS10);

	// for non-PWM output only - load the output compare A value of clock-1 value: force output compare
	// TCCR1C = (1<<FOC1A);

	// set the timer-1 PWM-A compare output: setting data port for output
	DDR_OC1A_REG |= (1<<DDR_OC1A);

}
