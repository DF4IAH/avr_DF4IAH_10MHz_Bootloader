################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/libs-device/osccal.c 

OBJS += \
./Src/libs-device/osccal.o 

C_DEPS += \
./Src/libs-device/osccal.d 


# Each subdirectory must supply rules for building sources it contributes
Src/libs-device/%.o: ../Src/libs-device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -DRELEASE -D__AVR_ATmega328P__ -DBOOTSIZE=2048 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


