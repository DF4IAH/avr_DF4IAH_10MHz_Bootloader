#!/bin/sh

avrdude -cusbasp -pm328p -Uflash:w:ISP__avr_DF4IAH_Bootloader.hex:i

