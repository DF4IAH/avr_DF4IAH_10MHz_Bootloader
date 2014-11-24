/*****************************************************************************
*
* AVRPROG compatible boot-loader
* Version  : 0.85 (Dec. 2008)
* Compiler : avr-gcc 4.1.2 / avr-libc 1.4.6
* size     : depends on features and startup ( minmal features < 512 words)
* by       : Martin Thomas, Kaiserslautern, Germany
*            eversmith@heizung-thomas.de
*            Additional code and improvements contributed by:
*           - Uwe Bonnes
*           - Bjoern Riemer
*           - Olaf Rempel
*
* License  : Copyright (c) 2006-2008 M. Thomas, U. Bonnes, O. Rempel
*            Free to use. You have to mention the copyright
*            owners in source-code and documentation of derived
*            work. No warranty! (Yes, you can insert the BSD
*            license here)
*
* Tested with ATmega8, ATmega16, ATmega162, ATmega32, ATmega324P,
*             ATmega644, ATmega644P, ATmega128, AT90CAN128
*
* - Initial versions have been based on the Butterfly bootloader-code
*   by Atmel Corporation (Authors: BBrandal, PKastnes, ARodland, LHM)
*
****************************************************************************
*
*  See the makefile and readme.txt for information on how to adapt 
*  the linker-settings to the selected Boot Size (BOOTSIZE=xxxx) and 
*  the MCU-type. Other configurations futher down in this file.
*
*  With BOOT_SIMPLE, minimal features and discarded int-vectors
*  this bootloader has should fit into a a 512 word (1024, 0x400 bytes) 
*  bootloader-section. 
*
****************************************************************************/
/*
	TODOs:
	- check lock-bits set
	- __bad_interrupt still linked even with modified 
	  linker-scripts which needs a default-handler,
	  "wasted": 3 words for AVR5 (>8kB), 2 words for AVR4
	- Check watchdog-disable-function in avr-libc.
*/
// tabsize: 4


#include <stdint.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "chipdef.h"
#include "main.h"
#include "df4iah_probe.h"
#include "df4iah_serial.h"
#include "df4iah_usb.h"
#include "df4iah_memory.h"
#include "df4iah_clkPullPwm.h"
#include "usbdrv/usbdrv.h"



// DATA SECTION

uint8_t gBuffer[SPM_PAGESIZE];
uint8_t timer0Snapshot = 0x00;
void (*jump_to_app)(void) = 0x0000;


// STRINGS IN CODE SECTION
PROGMEM const char gcs_AVR[gcs_AVR_len] = { 'A', 'V', 'R', 'B', 'O', 'O', 'T' };
PROGMEM const char gcs_FDL[gcs_FDL_len] = { 'F', 'D', 'L', ' ', VERSION_HIGH, VERSION_LOW };
PROGMEM const char gcs_E99[gcs_E99_len] = { '*', 'E', 'R', 'R', '-', '9', '9', '*' };


// CODE SECTION

/*
 * @see http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
 */

#if defined(BOOTLOADERHASNOVECTORS)
# warning "This Bootloader does not link interrupt vectors - see makefile"
/* make the linker happy - it wants to see __vector_default */
// void __vector_default(void) { ; }
void __vector_default(void) { ; }
#endif

/*  VECTOR - TABLE
 *
	Address	Labels	Code 					Comments
	0x0000			jmp RESET 				; Reset Handler
	0x0002			jmp EXT_INT0 			; IRQ0 Handler
	0x0004			jmp EXT_INT1 			; IRQ1 Handler
	0x0006			jmp PCINT0 				; PCINT0 Handler
	0x0008			jmp PCINT1 				; PCINT1 Handler
	0x000A			jmp PCINT2 				; PCINT2 Handler
	0x000C			jmp WDT 				; Watchdog Timer Handler
	0x000E			jmp TIM2_COMPA 			; Timer2 Compare A Handler
	0x0010			jmp TIM2_COMPB 			; Timer2 Compare B Handler
	0x0012			jmp TIM2_OVF 			; Timer2 Overflow Handler
	0x0014			jmp TIM1_CAPT 			; Timer1 Capture Handler
	0x0016			jmp TIM1_COMPA 			; Timer1 Compare A Handler
	0x0018			jmp TIM1_COMPB 			; Timer1 Compare B Handler
	0x001A			jmp TIM1_OVF 			; Timer1 Overflow Handler
	0x001C			jmp TIM0_COMPA 			; Timer0 Compare A Handler
	0x001E			jmp TIM0_COMPB 			; Timer0 Compare B Handler
	0x0020			jmp TIM0_OVF 			; Timer0 Overflow Handler
	0x0022			jmp SPI_STC 			; SPI Transfer Complete Handler
	0x0024			jmp USART_RXC 			; USART, RX Complete Handler
	0x0026			jmp USART_UDRE 			; USART, UDR Empty Handler
	0x0028			jmp USART_TXC 			; USART, TX Complete Handler
	0x002A			jmp ADC 				; ADC Conversion Complete Handler
	0x002C			jmp EE_RDY 				; EEPROM Ready Handler
	0x002E			jmp ANA_COMP 			; Analog Comparator Handler
	0x0030			jmp TWI 				; 2-wire Serial Interface Handler
	0x0032			jmp SPM_RDY 			; Store Program Memory Ready Handler
	;
	0x0033	RESET:	ldi r16, high(RAMEND)	; Main program start
	0x0034			out SPH,r16 			; Set Stack Pointer to top of RAM
 *
 */

//EMPTY_INTERRUPT(INT0_vect);
//EMPTY_INTERRUPT(INT1_vect);
//EMPTY_INTERRUPT(PCINT0_vect);
//EMPTY_INTERRUPT(PCINT1_vect);
//EMPTY_INTERRUPT(PCINT2_vect);
//EMPTY_INTERRUPT(WDT_vect);
//EMPTY_INTERRUPT(TIMER2_COMPA_vect);
//EMPTY_INTERRUPT(TIMER2_COMPB_vect);
//EMPTY_INTERRUPT(TIMER2_OVF_vect);
//EMPTY_INTERRUPT(TIMER1_CAPT_vect);
//EMPTY_INTERRUPT(TIMER1_COMPA_vect);
//EMPTY_INTERRUPT(TIMER1_COMPB_vect);
//EMPTY_INTERRUPT(TIMER1_OVF_vect);
//EMPTY_INTERRUPT(TIMER0_COMPA_vect);
//EMPTY_INTERRUPT(TIMER0_COMPB_vect);
//EMPTY_INTERRUPT(TIMER0_OVF_vect);
//EMPTY_INTERRUPT(SPI_STC_vect);
//EMPTY_INTERRUPT(USART_RX_vect);
//EMPTY_INTERRUPT(USART_UDRE_vect);
//EMPTY_INTERRUPT(USART_TX_vect);
//ISR(USART_TX_vect, ISR_ALIASOF(USART_RX_vect));
//EMPTY_INTERRUPT(ADC_vect);
//EMPTY_INTERRUPT(EE_READY_vect);
//EMPTY_INTERRUPT(ANALOG_COMP_vect);
//EMPTY_INTERRUPT(TWI_vect);
//EMPTY_INTERRUPT(SPM_READY_vect);

ISR(INT1_vect) {
	send_error_msg();
}


static inline void vectortable_to_bootloader(void) {
	asm volatile									// set active vector table into the Bootloader section
	(
		"ldi r24, %1\n\t"
		"out %0, r24\n\t"
		"ldi r24, %2\n\t"
		"out %0, r24\n\t"
		:
		: "i" (_SFR_IO_ADDR(MCUCR)),
		  "i" (1<<IVCE),
		  "i" (1<<IVSEL)
		: "r24"
	);
}

static inline void init_wdt() {
#ifdef DISABLE_WDT_AT_STARTUP
# ifdef WDT_OFF_SPECIAL
#   warning "using target specific watchdog_off"
	bootloader_wdt_off();
# else
	cli();
	wdt_reset();
	wdt_disable();
# endif
#endif
}

#if defined(START_POWERSAVE)
static void loop_powersave_loop()
{
	/*
		This is an adoption of the Butterfly Bootloader startup-sequence.
		It may look a little strange but separating the login-loop from
		the main parser-loop gives a lot of more possibilities (timeout, sleep-modes
	    etc.).
	*/
	for (;OK;) {
		if ((BLPIN & (1<<BLPNUM)) && (*((unsigned char*) 0x0000) != 0xff)) {
			// jump to main app if pin is not grounded
			BLPORT &= ~(1<<BLPNUM);					// set to default
#ifdef UART_DOUBLESPEED
			UART_STATUS &= ~(1<<UART_DOUBLE);
#endif
			jump_to_app();							// jump to application sector

		} else {
			val = recvchar();

			/* ESC */
			if (val == 0x1B) {
				// AVRPROG connection
				// wait for signon
				while (val != 'S')
					val = recvchar();

				send_boot();						// report signon
				OK = 0;

			} else {
				sendchar('?');
			}
		}

			// power-save code here
	}
}

#elif defined(START_SIMPLE)
static inline void simple_check()
{
	if ((BLPIN & (1<<BLPNUM)) && (*((unsigned short*) 0x0000) == 0x0c94)) {
		// jump to main app if pin is not grounded
		BLPORT &= ~(1<<BLPNUM);						// set to default
#ifdef UART_DOUBLESPEED
		UART_STATUS &= ~(1<<UART_DOUBLE);
#endif
		jump_to_app();								// jump to application sector
	}
}

#elif defined(START_WAIT)
static inline void wait_loop()
{
	uint16_t cnt = 0;

	for(;;) {
		if (UART_STATUS & (1<<UART_RXREADY))
			if (UART_DATA == START_WAIT_UARTCHAR)
				break;

		if (cnt++ >= WAIT_VALUE) {
			BLPORT &= ~(1<<BLPNUM);					// set to default
			jump_to_app();							// jump to application sector
		}

		_delay_ms(10);
	}
	send_boot();
}
#endif


void send_boot_msg()
{
	for (int i = 0; i < gcs_FDL_len; ++i) {
		sendchar(gcs_FDL[i]);
	}

//	for (int i = 0; i < gcs_AVR_len; ++i) {
//		sendchar(gcs_AVR[i]);
//	}
}

void send_error_msg()
{
	for (int i = 0; i < gcs_E99_len; ++i) {
		sendchar(gcs_E99[i]);
	}

	cli();
	sleep_cpu();
}


int main(void)
{
	uint16_t address = 0;
	uint8_t device = 0, val;
#ifdef START_POWERSAVE
	uint8_t OK = 1;
#endif

	vectortable_to_bootloader();
	init_probe();
	init_wdt();
	init_usb();
	init_serial();
	init_clkPullPwm();

    sei();							/* ENABLE interrupt */

#if defined(START_POWERSAVE)
	powersave_loop();

#elif defined(START_SIMPLE)
	simple_check();

#elif defined(START_WAIT)
	wait_loop();

#elif defined(START_BOOTICE)
# warning "BOOTICE mode - no startup-condition"

#else
# error "Select START_ condition for bootloader in main.c"
#endif

	for(;;) {
		val = recvchar();
		// Auto-Increment?
		if (val == 'a') {
			sendchar('Y');							// auto-increment is quicker

		// Write address
		} else if (val == 'A') {
			address = recvchar();					// read address 8 MSB
			address = (address<<8) | recvchar();
			sendchar('\r');

		// Buffer load support
		} else if (val == 'b') {
			sendchar('Y');							// report buffer load supported
			sendchar((sizeof(gBuffer) >> 8) & 0xFF);	// report buffer size in bytes
			sendchar(sizeof(gBuffer) & 0xFF);

		// Start buffer load
		} else if (val == 'B') {
			pagebuf_t size;
			size = recvchar() << 8;					// load high byte of buffersize
			size |= recvchar();						// load low byte of buffersize
			val = recvchar();						// load memory type ('E' or 'F')
			recvBuffer(size);

			if (device == DEVTYPE) {
				if (val == 'F') {
					address = writeFlashPage(address, size);
				} else if (val == 'E') {
					address = writeEEpromPage(address, size);
				}
				sendchar('\r');
			} else {
				sendchar(0);
			}

		// Block read
		} else if (val == 'g') {
			pagebuf_t size;
			size = recvchar() << 8;					// load high byte of buffersize
			size |= recvchar();						// load low byte of buffersize
			val = recvchar();						// get memtype

			if (val == 'F') {
				address = readFlashPage(address, size);
			} else if (val == 'E') {
				address = readEEpromPage(address, size);
			}

		// Chip erase
 		} else if (val == 'e') {
			if (device == DEVTYPE) {
				eraseFlash();
			}
			sendchar('\r');

		// Exit upgrade
		} else if (val == 'E') {
			wdt_enable(EXIT_WDT_TIME); 				// enable watchdog timer to give reset
			sendchar('\r');

#ifdef WRITELOCKBITS
#warning "Extension 'WriteLockBits' enabled"
		// TODO: does not work reliably
		// write lockbits
		} else if (val == 'l') {
			if (device == DEVTYPE) {
				// write_lock_bits(recvchar());
				boot_lock_bits_set(recvchar());		// boot.h takes care of mask
				boot_spm_busy_wait();
			}
			sendchar('\r');
#endif
		// Enter programming mode
		} else if (val == 'P') {
			sendchar('\r');

		// Leave programming mode
		} else if (val == 'L') {
			sendchar('\r');

		// return programmer type
		} else if (val == 'p') {
			sendchar('S');							// always serial programmer

#ifdef ENABLEREADFUSELOCK
#warning "Extension 'ReadFuseLock' enabled"
		// read "low" fuse bits
		} else if (val == 'F') {
			sendchar(read_fuse_lock(GET_LOW_FUSE_BITS));

		// read lock bits
		} else if (val == 'r') {
			sendchar(read_fuse_lock(GET_LOCK_BITS));

		// read high fuse bits
		} else if (val == 'N') {
			sendchar(read_fuse_lock(GET_HIGH_FUSE_BITS));

		// read extended fuse bits
		} else if (val == 'Q') {
			sendchar(read_fuse_lock(GET_EXTENDED_FUSE_BITS));
#endif

		// Return device type
		} else if (val == 't') {
			sendchar(DEVTYPE);
			sendchar(0);

		// clear and set LED ignored
		} else if ((val == 'x') || (val == 'y')) {
			recvchar();
			sendchar('\r');

		// set device
		} else if (val == 'T') {
			device = recvchar();
			sendchar('\r');

		// Return software identifier
		} else if (val == 'S') {
			send_boot_msg();

		// Return Software Version
		} else if (val == 'V') {
			sendchar(VERSION_HIGH);
			sendchar(VERSION_LOW);

		// return Signature Bytes (it seems that
		// AVRProg expects the "Atmel-byte" 0x1E last
		// but shows it first in the dialog-window)
		} else if (val == 's') {
			sendchar(SIG_BYTE3);
			sendchar(SIG_BYTE2);
			sendchar(SIG_BYTE1);

		/* ESC */
		} else if(val != 0x1b) {
			sendchar('?');
		}

#if defined(USE_USB)
		usbPoll();
#endif
	}

	return 0;
}
