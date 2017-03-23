################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/df4iah_bl_clkPullPwm.c \
../Src/df4iah_bl_main.c \
../Src/df4iah_bl_memory.c \
../Src/df4iah_bl_probe.c \
../Src/df4iah_bl_usb.c 

OBJS += \
./Src/df4iah_bl_clkPullPwm.o \
./Src/df4iah_bl_main.o \
./Src/df4iah_bl_memory.o \
./Src/df4iah_bl_probe.o \
./Src/df4iah_bl_usb.o 

C_DEPS += \
./Src/df4iah_bl_clkPullPwm.d \
./Src/df4iah_bl_main.d \
./Src/df4iah_bl_memory.d \
./Src/df4iah_bl_probe.d \
./Src/df4iah_bl_usb.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -DRELEASE -D__AVR_ATmega328P__ -DBOOTSIZE=2048 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


