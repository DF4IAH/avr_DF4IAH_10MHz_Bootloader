#!/bin/bash

avrdude -pm328p -cdragon_pp -u -Ulfuse:w:0xbf:m -Uhfuse:w:0xd8:m -Uefuse:w:0xfd:m -Uflash:w:../DF4IAH_10MHz_Bootloader_FW/DF4IAH_10MHz_Bootloader_FW/Release/avr_DF4IAH_Bootloader.hex:a

