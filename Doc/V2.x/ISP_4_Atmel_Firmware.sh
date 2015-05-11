#!/bin/sh

avrdude -cusbasp -pm328p -D -Uee:w:ISP__avr_DF4IAH_10MHz_Reference.eep:i
avrdude -cusbasp -pm328p -D -Uflash:w:ISP__avr_DF4IAH_10MHz_Reference.hex:i

