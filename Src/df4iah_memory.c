/*
 * df4iah_commands.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "df4iah_memory.h"

#include "df4iah_serial.h"

extern uint8_t gBuffer[SPM_PAGESIZE];


#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
void eraseFlash(void)
{
	// erase only main section (bootloader protection)
	uint32_t addr = 0;
	while (APP_END > addr) {
		boot_page_erase(addr);						// perform page erase
		boot_spm_busy_wait();						// wait until the memory is erased.
		addr += SPM_PAGESIZE;
	}
	boot_rww_enable();
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
uint16_t writeFlashPage(uint16_t waddr, pagebuf_t size)
{
	uint32_t pagestart = (uint32_t)waddr<<1;
	uint32_t baddr = pagestart;
	uint16_t data;
	uint8_t *tmp = gBuffer;

	do {
		data = *tmp++;
		data |= *tmp++ << 8;
		boot_page_fill(baddr, data);				// call asm routine.

		baddr += 2;									// select next word in memory
		size -= 2;									// reduce number of bytes to write by two
	} while (size);									// loop until all bytes written

	boot_page_write(pagestart);
	boot_spm_busy_wait();
	boot_rww_enable();								// re-enable the RWW section

	return baddr>>1;
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
uint16_t writeEEpromPage(uint16_t address, pagebuf_t size)
{
	uint8_t *tmp = gBuffer;

	do {
		eeprom_write_byte( (uint8_t*)address, *tmp++ );
		address++;									// select next byte
		size--;										// decrease number of bytes to write
	} while (size);									// loop until all bytes written

	// eeprom_busy_wait();

	return address;
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
uint16_t readFlashPage(uint16_t waddr, pagebuf_t size)
{
	uint32_t baddr = (uint32_t)waddr<<1;
	uint16_t data;

	do {
#ifndef READ_PROTECT_BOOTLOADER
#warning "Bootloader not read-protected"
#if defined(RAMPZ)
		data = pgm_read_word_far(baddr);
#else
		data = pgm_read_word_near(baddr);
#endif
#else
		// don't read bootloader
		if (baddr < APP_END) {
#if defined(RAMPZ)
			data = pgm_read_word_far(baddr);
#else
			data = pgm_read_word_near(baddr);
#endif
		}
		else {
			data = 0xFFFF; 							// fake empty
		}
#endif
		sendchar(data);								// send LSB
		sendchar((data >> 8));						// send MSB
		baddr += 2;									// select next word in memory
		size -= 2;									// subtract two bytes from number of bytes to read
	} while (size);									// repeat until block has been read

	return baddr>>1;
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
uint16_t readEEpromPage(uint16_t address, pagebuf_t size)
{
	do {
		sendchar( eeprom_read_byte( (uint8_t*)address ) );
		address++;
		size--;										// decrease number of bytes to read
	} while (size);									// repeat until block has been read

	return address;
}

#if defined(ENABLEREADFUSELOCK)
#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
uint8_t read_fuse_lock(uint16_t addr)
{
	uint8_t mode = (1<<BLBSET) | (1<<SELFPRGEN);
	uint8_t retval;

	asm volatile
	(
		"movw r30, %3\n\t"							/* Z to addr */ \
		"sts %0, %2\n\t"							/* set mode in SPM_REG */ \
		"lpm\n\t"									/* load fuse/lock value into r0 */ \
		"mov %1,r0\n\t"								/* save return value */ \
		: "=m" (SPM_REG),
		  "=r" (retval)
		: "r" (mode),
		  "r" (addr)
		: "r30", "r31", "r0"
	);
	return retval;
}
#endif
