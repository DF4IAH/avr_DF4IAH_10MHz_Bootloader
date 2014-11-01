/*
 * df4iah_commands.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_MEMORY_H_
#define DF4IAH_MEMORY_H_

/*
 * enable/disable readout of fuse and lock-bits
 * (AVRPROG has to detect the AVR correctly by device-code
 * to show the correct information).
 */
#define ENABLEREADFUSELOCK


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
