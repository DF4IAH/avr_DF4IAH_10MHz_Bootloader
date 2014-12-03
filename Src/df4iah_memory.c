/*
 * df4iah_commands.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "df4iah_memory.h"

#include "df4iah_serial.h"
#include "df4iah_usb.h"
#include "main.h"

#define min(a,b) (a) < (b) ?  (a) : (b)


#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
void eraseFlash(void)
{
	// erase only main section (bootloader protection)
	uint32_t addr = 0;
	while (APP_END >= addr) {
		boot_page_erase(addr);						// perform page erase
		boot_spm_busy_wait();						// wait until the memory is erased.
		addr += SPM_PAGESIZE;
	}
	boot_rww_enable();
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
void readFlashPage(uint8_t target[], pagebuf_t size, uint32_t baddr)
{
	uint16_t data;
	uint8_t idx = 0;

	while (size) {
#ifndef READ_PROTECT_BOOTLOADER
# warning "Bootloader not read-protected"
		if (true) {
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
		target[idx++] = data & 0xff;				// store LSB
		if (--size) {
			target[idx++] = data >> 8;				// store MSB
			baddr += 2;								// select next word in memory
			--size;									// subtract two bytes from number of bytes to read
		}
	}												// repeat until block has been read
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
void readEEpromPage(uint8_t target[], pagebuf_t size, uint16_t baddr)
{
	uint8_t idx = 0;

	while (size) {
		target[idx++] = eeprom_read_byte((uint8_t*) baddr++);
		--size;										// decrease number of bytes to read, repeat until block has been read
	}
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
void writeFlashPage(uint8_t source[], pagebuf_t size, uint32_t baddr)
{
	pagebuf_t sourceIdx = 0;

	while (size) {
		/* calculate */
		uint8_t  pageoffs  = baddr % SPM_PAGESIZE;
		uint32_t pagestart = baddr - pageoffs;
		uint8_t  len       = min(SPM_PAGESIZE - pageoffs, min(size, APP_END - baddr));
		uint8_t  trailer   = SPM_PAGESIZE - len;
		uint8_t  verifyCnt = 5;

		/* on each new page erase it first */
		if (!pageoffs) {
			boot_page_erase_safe(pagestart);		// perform page erase
		}

		while (--verifyCnt) {
			uint16_t data;

			/* fill buffer between pagestart and baddr first */
			for (uint8_t idx = 0; idx < pageoffs; ++idx) {
				uint16_t ptraddr = pagestart + idx;
				uint8_t bdata = *((uint8_t*) ptraddr);
				data = (idx % 1) ?  ((data & 0x00ff) | (bdata << 8))
										  : (0xff00  |  bdata);
				if (idx % 1) {
					boot_page_fill_safe(ptraddr & 0xfffffffe, data);	// call asm routine
				}
			}

			/* fill buffer with content */
			for (uint8_t idx = 0; idx < len; ++idx) {
				uint16_t ptraddr = baddr + idx;
				data = (ptraddr % 1) ?  ((data & 0x00ff) | (source[sourceIdx + idx] << 8))
											: (0xff00  |  source[sourceIdx + idx]);
				if (ptraddr % 1) {
					boot_page_fill_safe(ptraddr & 0xfffffffe, data);	// call asm routine
				}
			}

			/* fill buffer with trailing space */
			for (uint8_t idx = 0; idx < trailer; ++idx) {
				uint16_t ptraddr = baddr + len + idx;
				data = (ptraddr % 1) ?  ((data & 0x00ff) | 0xff00)
											: (0xff00  |   0xff);
				if (ptraddr % 1) {
					boot_page_fill_safe(ptraddr & 0xfffffffe, data);	// call asm routine
				}

				if (((idx + 1) == trailer) && (ptraddr % 1)) {
					boot_page_fill_safe((ptraddr + 2) & 0xfffffffe, data);	// call asm routine
				}
			}

			/* write the page */
			boot_page_write_safe(pagestart);

			/* verify data */
			uint8_t isValid = 1;
			for (uint8_t idx = 0; idx < len; ++idx) {
				uint16_t ptraddr = baddr + idx;
				if (*((uint8_t*) ptraddr) != source[sourceIdx + idx]) {
					isValid = 0;
					break;
				}
			}
			if (isValid) {
				if (!verifyCnt) {
					++verifyCnt;
				}
				break;
			}
		}
		if (!verifyCnt) {
			return;									// abort to write this page again
		}

		/* move pointers ahead */
		baddr     += len;
		size      -= len;
		sourceIdx += len;
	}
}

#ifdef RELEASE
__attribute__((section(".df4iah_memory"), aligned(2)))
#endif
void writeEEpromPage(uint8_t source[], pagebuf_t size, uint16_t baddr)
{
	uint8_t idx = 0;

	while (size--) {								// decrease number of bytes to write
		eeprom_write_byte((uint8_t*) baddr, source[idx++]);
		baddr++;									// select next byte
	}												// loop until all bytes written

	// eeprom_busy_wait();
}
