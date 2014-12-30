#ifndef _MEGA32_H_
#define _MEGA32_H_

/* Part-Code ISP */
#define DEVTYPE_ISP     	0x72
/* Part-Code Boot */
#define DEVTYPE_BOOT    	0x73

#define SIG_BYTE1			0x1E
#define SIG_BYTE2			0x95
#define SIG_BYTE3			0x02

/* USART */
#define UART_BAUD_HIGH		UBRR0H
#define UART_BAUD_LOW		UBRR0L
#define UART_STATUS			UCSR0A
#define UART_TXREADY		UDRE0
#define UART_RXREADY		RXC0
#define UART_DOUBLE			U2X0
#define UART_CTRL			UCSR0B
#define UART_CTRL_DATA		(_BV(TXEN0 | _BV(RXEN0))	// TX enable, RX enable
#define UART_CTRL2			UCSR0C
#define UART_CTRL2_DATA		(0b11 << UCSZ00)			// 8-bit
#define UART_DATA			UDR0
#define UART_PORT			PORTD						// port D register
#define UART_DDR			DDRD						// DDR for port D
#define UART_TX_PIN			PIND						// PIN for TX pin at port D
#define UART_TX_PNUM		PIN1						// PIN number for TX pin
#define UART_RX_PIN			PIND						// PIN for RX pin at port D
#define UART_RX_PNUM		PIN0						// PIN number for RX pin

/* Timer-n compare output */
#define DDR_OC0A_REG		DDRD
#define DDR_OC0A			PD6
#define DDR_OC0B_REG		DDRD
#define DDR_OC0B			PD5
#define DDR_OC1A_REG		DDRB
#define DDR_OC1A			PB1
#define DDR_OC1B_REG		DDRB
#define DDR_OC1B			PB2
#define DDR_OC2A_REG		DDRB
#define DDR_OC2A			PB3
#define DDR_OC2B_REG		DDRD
#define DDR_OC2B			PD3

/*
 * Pin "STARTPIN" on port "STARTPORT" in this port has to grounded
 * (active low) to start the bootloader
 */
#define PROBE_PORT			PORTD
#define PROBE_DDR			DDRD
#define PROBE_PIN			PIND
#define PROBE_PNUM			PIND3		// JP3 BootLoader

/* PWM Debugging toggle pin */
#define PWMTOGGLEPIN_DDR	DDRC
#define PWMTOGGLEPIN_PORT	PORTC
#define PWMTOGGLEPIN_PIN	PINC
#define PWMTOGGLEPIN_PNUM	PIN5		// PC5(ADC5/SCL) - Pin 28

/* BOOT token and place of BOOT token as offset before RAMEND */
# define BOOT_TOKEN			0xb00f
# define BOOT_TOKEN_EE_ADR	0x3fa		// @see df4iah_fw_memory.h

#endif // #ifndef _MEGA32_H_
