################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/usbdrv_bl/oddebug.c \
../Src/usbdrv_bl/usbdrv.c 

S_UPPER_SRCS += \
../Src/usbdrv_bl/usbdrvasm.S 

ASM_SRCS += \
../Src/usbdrv_bl/usbdrvasm.asm 

OBJS += \
./Src/usbdrv_bl/oddebug.o \
./Src/usbdrv_bl/usbdrv.o \
./Src/usbdrv_bl/usbdrvasm.o 

C_DEPS += \
./Src/usbdrv_bl/oddebug.d \
./Src/usbdrv_bl/usbdrv.d 

ASM_DEPS += \
./Src/usbdrv_bl/usbdrvasm.d 

S_UPPER_DEPS += \
./Src/usbdrv_bl/usbdrvasm.d 


# Each subdirectory must supply rules for building sources it contributes
Src/usbdrv_bl/%.o: ../Src/usbdrv_bl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -DRELEASE -D__AVR_ATmega328P__ -DBOOTSIZE=2048 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/usbdrv_bl/%.o: ../Src/usbdrv_bl/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/usbdrv_bl/%.o: ../Src/usbdrv_bl/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


