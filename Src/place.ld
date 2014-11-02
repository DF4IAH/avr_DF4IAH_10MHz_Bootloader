#  -M -T place.ld


SECTIONS {
  .data 0x900100 :
    {
    CREATE_OBJECT_SYMBOLS
    *(.data)
    }
  
  .text 0x7000 :
    {
    CREATE_OBJECT_SYMBOLS
    *(.text)
    _etext = ALIGN(0x0200);
    }
}


Address of section .data set to 0x800100
LOAD /usr/lib/gcc/avr/4.8.2/../../../avr/lib/avr5/crtm328p.o
Address of section .text set to 0x7000
LOAD ./Src/usbdrv/oddebug.o
LOAD ./Src/usbdrv/usbdrv.o
LOAD ./Src/usbdrv/usbdrvasm.o
LOAD ./Src/libs-device/osccal.o
Address set to 0x7800
LOAD ./Src/df4iah_memory.o
LOAD ./Src/df4iah_probe.o
LOAD ./Src/df4iah_serial.o
LOAD ./Src/df4iah_usb.o
LOAD ./Src/main.o
START GROUP
LOAD /usr/lib/gcc/avr/4.8.2/avr5/libgcc.a
LOAD /usr/lib/gcc/avr/4.8.2/../../../avr/lib/avr5/libm.a
LOAD /usr/lib/gcc/avr/4.8.2/../../../avr/lib/avr5/libc.a
END GROUP
