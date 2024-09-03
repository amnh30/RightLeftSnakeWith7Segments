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
RightLeftSnakeWith7Segments.lss \

FLASH_IMAGE += \
RightLeftSnakeWith7Segments.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: RightLeftSnakeWith7Segments.elf secondary-outputs

# Tool invocations
RightLeftSnakeWith7Segments.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RightLeftSnakeWith7Segments.map -mmcu=atmega32 -o "RightLeftSnakeWith7Segments.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RightLeftSnakeWith7Segments.lss: RightLeftSnakeWith7Segments.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RightLeftSnakeWith7Segments.elf  >"RightLeftSnakeWith7Segments.lss"
	@echo 'Finished building: $@'
	@echo ' '

RightLeftSnakeWith7Segments.hex: RightLeftSnakeWith7Segments.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RightLeftSnakeWith7Segments.elf  "RightLeftSnakeWith7Segments.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RightLeftSnakeWith7Segments.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 RightLeftSnakeWith7Segments.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RightLeftSnakeWith7Segments.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
