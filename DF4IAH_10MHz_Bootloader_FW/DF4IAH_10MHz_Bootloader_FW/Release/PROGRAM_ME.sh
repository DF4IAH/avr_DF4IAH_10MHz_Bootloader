#!/bin/sh

avrdude -cdragon_pp -pm328p -Ulfuse:w:0xbf:m -Uhfuse:w:0xd8:m -Uefuse:w:0xfd:m -Ufl:w:DF4IAH_10MHz_Bootloader_FW.hex

