/*
 * main.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef MAIN_H_
#define MAIN_H_

/* MCU frequency */
#ifndef F_CPU
// #define F_CPU 7372800
#define F_CPU (7372800 / 2)
#endif

/* Device-Type:
   For AVRProg the BOOT-option is preferred
   which is the "correct" value for a bootloader.
   avrdude may only detect the part-code for ISP */
#define DEVTYPE     DEVTYPE_BOOT
// #define DEVTYPE     DEVTYPE_ISP

/*
 * Define if Watchdog-Timer should be disable at startup
 */
#define DISABLE_WDT_AT_STARTUP

/*
 * Watchdog-reset is issued at exit
 * define the timeout-value here (see avr-libc manual)
 */
#define EXIT_WDT_TIME	WDTO_250MS

/* wait-time for START_WAIT mode ( t = WAIT_TIME * 10ms ) */
#define WAIT_VALUE 100 /* here: 100*10ms = 1000ms = 1sec */


#define VERSION_HIGH '141'
#define VERSION_LOW  '204'

#ifndef GET_LOCK_BITS
# define GET_LOCK_BITS           0x0001
# define GET_LOW_FUSE_BITS       0x0000
# define GET_HIGH_FUSE_BITS      0x0003
# define GET_EXTENDED_FUSE_BITS  0x0002
#endif


// STRINGS IN CODE SECTION
#define gcs_AVR_len  7
#define gcs_FDL_len  6
#define gcs_E99_len  8


void give_away(void);

int main(void);

#endif /* MAIN_H_ */
