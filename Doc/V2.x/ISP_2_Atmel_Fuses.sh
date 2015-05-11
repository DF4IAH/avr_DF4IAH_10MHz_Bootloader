#!/bin/sh

avrdude -cusbasp -pm328p -u -D -Ulfuse:w:0xbf:m -Uhfuse:w:0xd8:m -Uefuse:w:0xfd:m

