################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./aic3204_tone_headphone.obj" \
"./aic3204_test.obj" \
"./aic3204_loop_stereo_in1.obj" \
-l"usbstk5515bsl.lib" \
-l"rts55x_eh.lib" \
"../lnkx.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: aic3204.out

# Tool invocations
aic3204.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g -O3 --diag_warning=225 --ptrdiff_size=32 --memory_model=large -k --asm_listing -z -m"aic3204.map" --warn_sections -i"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include" -i"C:/Users/Kurt/Documents/Little_Projects/MCUs/C5515/usbstk5515_BSL_RevA/usbstk5515_v1/tests/aic3204/../../lib" --reread_libs --rom_model -o "aic3204.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QUOTED) "aic3204.out"
	-$(RM) "aic3204_loop_stereo_in1.pp" "aic3204_test.pp" "aic3204_tone_headphone.pp" "main.pp" 
	-$(RM) "aic3204_loop_stereo_in1.obj" "aic3204_test.obj" "aic3204_tone_headphone.obj" "main.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
