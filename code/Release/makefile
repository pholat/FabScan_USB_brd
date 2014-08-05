################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include usbdrv/subdir.mk
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
avr_at2313_vusb_fabscan.lss \

FLASH_IMAGE += \
avr_at2313_vusb_fabscan.hex \

EEPROM_IMAGE += \
avr_at2313_vusb_fabscan.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: avr_at2313_vusb_fabscan.elf secondary-outputs

# Tool invocations
avr_at2313_vusb_fabscan.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,avr_at2313_vusb_fabscan.map -mmcu=attiny2313 -o "avr_at2313_vusb_fabscan.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

avr_at2313_vusb_fabscan.lss: avr_at2313_vusb_fabscan.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S avr_at2313_vusb_fabscan.elf  >"avr_at2313_vusb_fabscan.lss"
	@echo 'Finished building: $@'
	@echo ' '

avr_at2313_vusb_fabscan.hex: avr_at2313_vusb_fabscan.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex avr_at2313_vusb_fabscan.elf  "avr_at2313_vusb_fabscan.hex"
	@echo 'Finished building: $@'
	@echo ' '

avr_at2313_vusb_fabscan.eep: avr_at2313_vusb_fabscan.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex avr_at2313_vusb_fabscan.elf  "avr_at2313_vusb_fabscan.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: avr_at2313_vusb_fabscan.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 avr_at2313_vusb_fabscan.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) avr_at2313_vusb_fabscan.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
