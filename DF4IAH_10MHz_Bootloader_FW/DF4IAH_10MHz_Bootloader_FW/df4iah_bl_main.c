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
******************************************************************************
*
*  See the makefile and readme.txt for information on how to adapt 
*  the linker-settings to the selected Boot Size (BOOTSIZE=xxxx) and 
*  the MCU-type. Other configurations futher down in this file.
*
*  With BOOT_SIMPLE, minimal features and discarded int-vectors
*  this bootloader has should fit into a a 512 word (1024, 0x400 bytes) 
*  bootloader-section. 
*
******************************************************************************/
// tabsize: 4

/**
 * Memory layout - BOOTLOADER:
 * 		Start			Length
 * 		BL: text		0x7000		0x0744
 * 		bl_ClkPullPwm	0x7780		0x0052
 * 		bl_Probe		0x78C0		0x003c
 * 		bl_Memory		0x7900		0x02c8
 * 		bl_USB			0x7be0		0x03fc
 */


#include <stdint.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "chipdef.h"
#include "df4iah_bl_main.h"
#include "df4iah_bl_probe.h"
#include "df4iah_bl_usb.h"
#include "df4iah_bl_memory.h"
#include "df4iah_bl_clkPullPwm.h"
#include "usbdrv_bl/usbdrv.h"


// DATA SECTION

/* df4iah_bl_main */
void (*jump_to_app)(void) 									= (void*) 0x0000;
volatile uint8_t timer0Snapshot 							= 0x00;
uint8_t mainIsJumperBlSet									= false;
uint8_t mainStopAvr 										= false;
usbTxStatus_t usbTxStatus1, usbTxStatus3;


// STRINGS IN CODE SECTION
// PROGMEM const char VENDOR[VENDOR_len] = { 'D', 'F', '4', 'I', 'A', 'H' };


// CODE SECTION

/*
 * @see http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
 */

#if defined(BOOTLOADERHASNOVECTORS)
# warning "This Bootloader does not link interrupt vectors - see makefile"
/* make the linker happy - it wants to see __vector_default */
void __vector_default(void) { ; }
#endif

/*  VECTOR - TABLE
 *
	Address	Labels	Code 					Comments
	0x7000			jmp RESET 				; Reset Handler
	0x7002			jmp EXT_INT0 			; IRQ0 Handler
	0x7004			jmp EXT_INT1 			; IRQ1 Handler
	0x7006			jmp PCINT0 				; PCINT0 Handler
	0x7008			jmp PCINT1 				; PCINT1 Handler
	0x700A			jmp PCINT2 				; PCINT2 Handler
	0x700C			jmp WDT 				; Watchdog Timer Handler
	0x700E			jmp TIM2_COMPA 			; Timer2 Compare A Handler
	0x7010			jmp TIM2_COMPB 			; Timer2 Compare B Handler
	0x7012			jmp TIM2_OVF 			; Timer2 Overflow Handler
	0x7014			jmp TIM1_CAPT 			; Timer1 Capture Handler
	0x7016			jmp TIM1_COMPA 			; Timer1 Compare A Handler
	0x7018			jmp TIM1_COMPB 			; Timer1 Compare B Handler
	0x701A			jmp TIM1_OVF 			; Timer1 Overflow Handler
	0x701C			jmp TIM0_COMPA 			; Timer0 Compare A Handler
	0x701E			jmp TIM0_COMPB 			; Timer0 Compare B Handler
	0x7020			jmp TIM0_OVF 			; Timer0 Overflow Handler
	0x7022			jmp SPI_STC 			; SPI Transfer Complete Handler
	0x7024			jmp USART_RXC 			; USART, RX Complete Handler
	0x7026			jmp USART_UDRE 			; USART, UDR Empty Handler
	0x7028			jmp USART_TXC 			; USART, TX Complete Handler
	0x702A			jmp ADC 				; ADC Conversion Complete Handler
	0x702C			jmp EE_RDY 				; EEPROM Ready Handler
	0x702E			jmp ANA_COMP 			; Analog Comparator Handler
	0x7030			jmp TWI 				; 2-wire Serial Interface Handler
	0x7032			jmp SPM_RDY 			; Store Program Memory Ready Handler
	;
	0x7033	RESET:	ldi r16, high(RAMEND)	; Main program start
	0x7034			out SPH,r16 			; Set Stack Pointer to top of RAM
 *
 */

//EMPTY_INTERRUPT(INT0_vect);
//EMPTY_INTERRUPT(INT1_vect);
//ISR(INT1_vect, ISR_ALIASOF(INT0_vect));
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
//EMPTY_INTERRUPT(ADC_vect);
//EMPTY_INTERRUPT(EE_READY_vect);
//EMPTY_INTERRUPT(ANALOG_COMP_vect);
//EMPTY_INTERRUPT(TWI_vect);
//EMPTY_INTERRUPT(SPM_READY_vect);

//ISR(INT1_vect) {
//	send_error_msg();
//}


static inline void vectortable_to_bootloader(void) {
	cli();
	asm volatile											// set active vector table into the Bootloader section
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

static inline void wdt_init() {
	wdt_disable();
}

static inline void app_startup_check()
{
	// look for a BOOT marker in the EEPROM and do not jump to the Firmware when it is found at its place
	uint16_t tokenVal = 0;
	memory_bl_readEEpromPage((uint8_t*) &tokenVal, sizeof(tokenVal), BOOT_TOKEN_EE_ADR);
	if (tokenVal != BOOT_TOKEN) {
		// check for jumper-setting and for a valid jump-table entry
		uint16_t code =  0;
		memory_bl_readFlashPage((uint8_t*) &code, sizeof(code), 0x0000);
		if ((!mainIsJumperBlSet) && (code != 0xffff)) {		// is programmed
			probe_bl_close();
			cli();
			jump_to_app();									// jump to firmware section
		}

	} else {
		/* INHIBIT jump_to_app() - remove one time token */
		uint16_t clearVal = 0xffff;
		memory_bl_writeEEpromPage((uint8_t*) &clearVal, sizeof(clearVal), BOOT_TOKEN_EE_ADR);
	}
}

void give_away(void)
{
	wdt_reset();
	usbPoll();
	clkPullPwm_bl_togglePin();
}


int main(void)
{
	cli();
	vectortable_to_bootloader();

	PRR    = 0xEF;											// disable all modules within the Power Reduction Register
	ACSR  |= _BV(ACD);										// switch on Analog Comparator Disable
	DIDR1 |= (0b11 << AIN0D);								// disable digital input buffers on AIN0 and AIN1

	// switch off Pull-Up Disable
	MCUCR &= ~(_BV(PUD));

	for (;;) {
		wdt_init();
		probe_bl_init();
		app_startup_check();								// try to jump to the application FIRMWARE, else return

		clkPullPwm_bl_init();
		usb_bl_init();										// starts at 67 ms after power-up, ends at 316 ms after power-up

		mainStopAvr = false;
		sei();												// ENABLE interrupt
		while(!mainStopAvr) {								// falls out when DISCONNECT message is received
			give_away();
		}
		cli();												// DISABLE interrupt

		usb_bl_close();
		clkPullPwm_bl_close();
		//	probe_bl_close();
		//	wdt_close();
	}

	return 0;
}
