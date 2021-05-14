################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
vez6zad2.lss \

FLASH_IMAGE += \
vez6zad2.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: vez6zad2.elf secondary-outputs

# Tool invocations
vez6zad2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,vez6zad2.map -L"C:\Users\Dusan\Desktop\RSZDMK\usart\Release" -mmcu=atmega328p -o "vez6zad2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

vez6zad2.lss: vez6zad2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S vez6zad2.elf  >"vez6zad2.lss"
	@echo 'Finished building: $@'
	@echo ' '

vez6zad2.hex: vez6zad2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex vez6zad2.elf  "vez6zad2.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: vez6zad2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p vez6zad2.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: vez6zad2.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm328p -carduino -PCOM6 -Uflash:w:vez6zad2.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) vez6zad2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
