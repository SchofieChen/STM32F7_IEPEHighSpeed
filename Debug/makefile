################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Inc/TransformFunctions/subdir.mk
-include Core/Inc/SupportFunctions/subdir.mk
-include Core/Inc/StatisticsFunctions/subdir.mk
-include Core/Inc/MatrixFunctions/subdir.mk
-include Core/Inc/FilteringFunctions/subdir.mk
-include Core/Inc/FastMathFunctions/subdir.mk
-include Core/Inc/ControllerFunctions/subdir.mk
-include Core/Inc/ComplexMathFunctions/subdir.mk
-include Core/Inc/CommonTables/subdir.mk
-include Core/Inc/BasicMathFunctions/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

BUILD_ARTIFACT_NAME := STM32F7_HighSpeed_IEPE
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32F7_HighSpeed_IEPE.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F7_HighSpeed_IEPE.list \

OBJCOPY_HEX += \
STM32F7_HighSpeed_IEPE.hex \

OBJCOPY_BIN += \
STM32F7_HighSpeed_IEPE.bin \


# All Target
all: main-build

# Main-build Target
main-build: STM32F7_HighSpeed_IEPE.elf secondary-outputs

# Tool invocations
STM32F7_HighSpeed_IEPE.elf: $(OBJS) $(USER_OBJS) E:\UMC\STM32F7_IEPEHighSpeed\STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "STM32F7_HighSpeed_IEPE.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"E:\UMC\STM32F7_IEPEHighSpeed\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F7_HighSpeed_IEPE.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F7_HighSpeed_IEPE.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F7_HighSpeed_IEPE.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32F7_HighSpeed_IEPE.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "STM32F7_HighSpeed_IEPE.hex"
	@echo 'Finished building: $@'
	@echo ' '

STM32F7_HighSpeed_IEPE.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32F7_HighSpeed_IEPE.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
