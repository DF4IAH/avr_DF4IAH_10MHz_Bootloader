################################################################################
# Automatically-generated file. Do not edit!
################################################################################


RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../usbdrv_bl


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../df4iah_bl_clkPullPwm.c \
../df4iah_bl_main.c \
../df4iah_bl_memory.c \
../df4iah_bl_probe.c \
../df4iah_bl_usb.c \
../usbdrv_bl/oddebug.c \
../usbdrv_bl/usbdrv.c


PREPROCESSING_SRCS +=  \
../usbdrv_bl/usbdrvasm.S


ASM_SRCS += 


OBJS +=  \
df4iah_bl_clkPullPwm.o \
df4iah_bl_main.o \
df4iah_bl_memory.o \
df4iah_bl_probe.o \
df4iah_bl_usb.o \
usbdrv_bl/oddebug.o \
usbdrv_bl/usbdrv.o \
usbdrv_bl/usbdrvasm.o

OBJS_AS_ARGS +=  \
df4iah_bl_clkPullPwm.o \
df4iah_bl_main.o \
df4iah_bl_memory.o \
df4iah_bl_probe.o \
df4iah_bl_usb.o \
usbdrv_bl/oddebug.o \
usbdrv_bl/usbdrv.o \
usbdrv_bl/usbdrvasm.o

C_DEPS +=  \
df4iah_bl_clkPullPwm.d \
df4iah_bl_main.d \
df4iah_bl_memory.d \
df4iah_bl_probe.d \
df4iah_bl_usb.d \
usbdrv_bl/oddebug.d \
usbdrv_bl/usbdrv.d \
usbdrv_bl/usbdrvasm.d

C_DEPS_AS_ARGS +=  \
df4iah_bl_clkPullPwm.d \
df4iah_bl_main.d \
df4iah_bl_memory.d \
df4iah_bl_probe.d \
df4iah_bl_usb.d \
usbdrv_bl/oddebug.d \
usbdrv_bl/usbdrv.d \
usbdrv_bl/usbdrvasm.d

OUTPUT_FILE_PATH +=DF4IAH_10MHz_Bootloader_FW.elf

OUTPUT_FILE_PATH_AS_ARGS +=DF4IAH_10MHz_Bootloader_FW.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DNDEBUG -DRELEASE -DF_CPU=20000 -DUSB_CFG_CLOCK_KHZ=20000 -DBOOTSIZE=2048  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

usbdrv_bl/%.o: ../usbdrv_bl/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DNDEBUG -DRELEASE -DF_CPU=20000 -DUSB_CFG_CLOCK_KHZ=20000 -DBOOTSIZE=2048  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
usbdrv_bl/usbdrvasm.o: ../usbdrv_bl/usbdrvasm.S
	@echo Building file: $<
	@echo Invoking: AVR/GNU Assembler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega328p" -DUSB_CFG_CLOCK_KHZ=20000 -I "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	


usbdrv_bl/%.o: ../usbdrv_bl/%.S
	@echo Building file: $<
	@echo Invoking: AVR/GNU Assembler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega328p" -DUSB_CFG_CLOCK_KHZ=20000 -I "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="DF4IAH_10MHz_Bootloader_FW.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -Wl,-section-start=.df4iah_bl_clkpullpwm=0x7780 -Wl,-section-start=.df4iah_bl_probe=0x78c0 -Wl,-section-start=.df4iah_bl_memory=0x7900 -Wl,-section-start=.df4iah_bl_usb=0x7be0  -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega328p" -Ttext=0x7000 -mrelax  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "DF4IAH_10MHz_Bootloader_FW.elf" "DF4IAH_10MHz_Bootloader_FW.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "DF4IAH_10MHz_Bootloader_FW.elf" "DF4IAH_10MHz_Bootloader_FW.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "DF4IAH_10MHz_Bootloader_FW.elf" > "DF4IAH_10MHz_Bootloader_FW.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "DF4IAH_10MHz_Bootloader_FW.elf" "DF4IAH_10MHz_Bootloader_FW.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "DF4IAH_10MHz_Bootloader_FW.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "DF4IAH_10MHz_Bootloader_FW.elf" "DF4IAH_10MHz_Bootloader_FW.a" "DF4IAH_10MHz_Bootloader_FW.hex" "DF4IAH_10MHz_Bootloader_FW.lss" "DF4IAH_10MHz_Bootloader_FW.eep" "DF4IAH_10MHz_Bootloader_FW.map" "DF4IAH_10MHz_Bootloader_FW.srec" "DF4IAH_10MHz_Bootloader_FW.usersignatures"
	