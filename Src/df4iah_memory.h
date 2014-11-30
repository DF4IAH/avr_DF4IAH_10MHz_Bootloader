/*
 * df4iah_commands.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_MEMORY_H_
#define DF4IAH_MEMORY_H_


/*
 * define the following if the bootloader should not output
 * itself at flash read (will fake an empty boot-section)
 */
#define READ_PROTECT_BOOTLOADER


#include <stdint.h>

#include "chipdef.h"


void eraseFlash(void);

void readFlashPage(uint8_t target[], pagebuf_t size, uint32_t baddr);
void readEEpromPage(uint8_t target[], pagebuf_t size, uint16_t baddr);
void writeFlashPage(uint8_t source[], pagebuf_t size, uint32_t baddr);
void writeEEpromPage(uint8_t source[], pagebuf_t size, uint16_t baddr);


#endif /* DF4IAH_MEMORY_H_ */
