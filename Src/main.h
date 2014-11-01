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

/*
 * Select startup-mode
 * SIMPLE-Mode - Jump to bootloader main BL-loop if key is
 *   pressed (Pin grounded) "during" reset or jump to the
 *   application if the pin is not grounded. The internal
 *   pull-up resistor is enabled during the startup and
 *   gets disabled before the application is started.
 * POWERSAVE-Mode - Startup is separated in two loops
 *   which makes power-saving a little easier if no firmware
 *   is on the chip. Needs more memory
 * BOOTICE-Mode - to flash the JTAGICE upgrade.ebn file.
 *   No startup-sequence in this mode. Jump directly to the
 *   parser-loop on reset
 *   F_CPU in BOOTICEMODE must be 7372800 Hz to be compatible
 *   with the org. JTAGICE-Firmware
 * WAIT-mode waits 1 sec for the defined character if nothing
 *    is received then the user prog is started.
 */
#define START_SIMPLE
//#define START_WAIT
//#define START_POWERSAVE
//#define START_BOOTICE

/* character to start the bootloader in mode START_WAIT */
#define START_WAIT_UARTCHAR 'S'

/* wait-time for START_WAIT mode ( t = WAIT_TIME * 10ms ) */
#define WAIT_VALUE 100 /* here: 100*10ms = 1000ms = 1sec */

/* enable/disable write of lock-bits
 * WARNING: lock-bits can not be reseted by the bootloader (as far as I know)
 * Only protection no unprotection, "chip erase" from bootloader only
 * clears the flash but does no real "chip erase" (this is not possible
 * with a bootloader as far as I know)
 * Keep this undefined!
 */
//#define WRITELOCKBITS

/*
 * define the following if the bootloader should not output
 * itself at flash read (will fake an empty boot-section)
 */
//#define READ_PROTECT_BOOTLOADER


#define VERSION_HIGH '0'
#define VERSION_LOW  '8'

#define GET_LOCK_BITS           0x0001
#define GET_LOW_FUSE_BITS       0x0000
#define GET_HIGH_FUSE_BITS      0x0003
#define GET_EXTENDED_FUSE_BITS  0x0002



#endif /* MAIN_H_ */
