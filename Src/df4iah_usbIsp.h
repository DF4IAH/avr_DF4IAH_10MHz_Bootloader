/*
 * isp.h - part of USBasp
 *
 * Autor..........: Thomas Fischl <tfischl@gmx.de>
 * Description....: Provides functions for communication/programming
 *                  over ISP interface
 * Licence........: GNU GPL v2 (see Readme.txt)
 * Creation Date..: 2005-02-23
 * Last change....: 2009-02-28
 */

#ifndef DF4IAH_USBISP_H_
#define	DF4IAH_USBISP_H_

#ifndef uchar
#define	uchar	unsigned char
#endif

#define	ISP_OUT   PORTB
#define ISP_IN    PINB
#define ISP_DDR   DDRB
#define ISP_RST   PB2
#define ISP_MOSI  PB3
#define ISP_MISO  PB4
#define ISP_SCK   PB5

/* Prepare connection to target device */
void ispConnect();

/* Close connection to target device */
void ispDisconnect();

/* read an write a byte from ISP using software (slow) */
uchar ispTransmit_sw(uchar send_byte);

/* read an write a byte from ISP using hardware (fast) */
uchar ispTransmit_hw(uchar send_byte);

/* enter programming mode */
uchar ispEnterProgrammingMode();

/* read byte from EEPROM at given address */
uchar ispReadEEPROM(unsigned int address);

/* write byte to Flash at given address */
uchar ispWriteFlash(unsigned long address, uchar data, uchar pollmode);

uchar ispFlushPage(unsigned long address, uchar pollvalue);

/* read byte from Flash at given address */
uchar ispReadFlash(unsigned long address);

/* write byte to EEPROM at given address */
uchar ispWriteEEPROM(unsigned int address, uchar data);

/* pointer to SW or HW transmit function */
uchar (*ispTransmit)(uchar);

/* set SCK speed. call before ispConnect! */
void ispSetSCKOption(uchar sckoption);

/* load extended address byte */
void ispLoadExtendedAddressByte(unsigned long address);

#endif /* DF4IAH_USBISP_H_ */
