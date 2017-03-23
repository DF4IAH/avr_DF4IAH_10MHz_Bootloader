################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/usbdrv_bl/subdir.mk
-include Src/libs-device/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
avr_DF4IAH_Bootloader.lss \

FLASH_IMAGE += \
avr_DF4IAH_Bootloader.hex \

EEPROM_IMAGE += \
avr_DF4IAH_Bootloader.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: avr_DF4IAH_Bootloader.elf secondary-outputs

# Tool invocations
avr_DF4IAH_Bootloader.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,avr_DF4IAH_Bootloader.map -Wl,--section-start=.text=0x7000  -Wl,--section-start=.df4iah_bl_memory=0x7900  -Wl,--section-start=.df4iah_bl_probe=0x78C0  -Wl,--section-start=.df4iah_bl_usb=0x7BE0 -Wl,--section-start=.df4iah_bl_clkpullpwm=0x7780 -mmcu=atmega328p -o "avr_DF4IAH_Bootloader.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

avr_DF4IAH_Bootloader.lss: avr_DF4IAH_Bootloader.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S avr_DF4IAH_Bootloader.elf  >"avr_DF4IAH_Bootloader.lss"
	@echo 'Finished building: $@'
	@echo ' '

avr_DF4IAH_Bootloader.hex: avr_DF4IAH_Bootloader.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex avr_DF4IAH_Bootloader.elf  "avr_DF4IAH_Bootloader.hex"
	@echo 'Finished building: $@'
	@echo ' '

avr_DF4IAH_Bootloader.eep: avr_DF4IAH_Bootloader.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex avr_DF4IAH_Bootloader.elf  "avr_DF4IAH_Bootloader.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: avr_DF4IAH_Bootloader.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=sysv -x avr_DF4IAH_Bootloader.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) avr_DF4IAH_Bootloader.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
