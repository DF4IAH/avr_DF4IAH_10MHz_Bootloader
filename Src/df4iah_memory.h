/*
 * df4iah_commands.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_MEMORY_H_
#define DF4IAH_MEMORY_H_


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
#define READ_PROTECT_BOOTLOADER

/*
 * enable/disable readout of fuse and lock-bits
 * (AVRPROG has to detect the AVR correctly by device-code
 * to show the correct information).
 */
//#define ENABLEREADFUSELOCK


#include <stdint.h>

#include "chipdef.h"



void eraseFlash(void);

uint16_t writeFlashPage(uint16_t waddr, pagebuf_t size);

uint16_t writeEEpromPage(uint16_t address, pagebuf_t size);

uint16_t readFlashPage(uint16_t waddr, pagebuf_t size);

uint16_t readEEpromPage(uint16_t address, pagebuf_t size);

#if defined(ENABLEREADFUSELOCK)
uint8_t read_fuse_lock(uint16_t addr);
#endif


#endif /* DF4IAH_MEMORY_H_ */
