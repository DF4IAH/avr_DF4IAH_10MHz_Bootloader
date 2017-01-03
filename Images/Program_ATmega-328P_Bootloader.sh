#!/bin/bash

avrdude -pm328p -cdragon_pp -u -Ulfuse:w:0xbf:m -Uhfuse:w:0xd8:m -Uefuse:w:0xfd:m -Uflash:w:Release/avr_DF4IAH_Bootloader.hex:a

