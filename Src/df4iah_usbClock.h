/*
 * clock.h - part of USBasp
 *
 * Autor..........: Thomas Fischl <tfischl@gmx.de>
 * Description....: Provides functions for timing/waiting
 * Licence........: GNU GPL v2 (see Readme.txt)
 * Creation Date..: 2005-02-23
 * Last change....: 2006-11-16
 */

#ifndef DF4IAH_USBCLOCK_H_
#define	DF4IAH_USBCLOCK_H_

#define TIMERVALUE      TCNT0
#define CLOCK_T_320us	60

/* set prescaler to 64 */
// #define clockInit()  TCCR0B = (1 << CS01) | (1 << CS00);
#define clockInit()  { }

/* wait time * 320 us */
void clockWait(uint8_t time);

#endif /* DF4IAH_USBCLOCK_H_ */
