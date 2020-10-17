################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../aic3204_loop_stereo_in1.c \
../aic3204_test.c \
../aic3204_tone_headphone.c \
../main.c 

CMD_SRCS += \
../lnkx.cmd 

OBJS += \
./aic3204_loop_stereo_in1.obj \
./aic3204_test.obj \
./aic3204_tone_headphone.obj \
./main.obj 

C_DEPS += \
./aic3204_loop_stereo_in1.pp \
./aic3204_test.pp \
./aic3204_tone_headphone.pp \
./main.pp 

C_DEPS__QUOTED += \
"aic3204_loop_stereo_in1.pp" \
"aic3204_test.pp" \
"aic3204_tone_headphone.pp" \
"main.pp" 

OBJS__QUOTED += \
"aic3204_loop_stereo_in1.obj" \
"aic3204_test.obj" \
"aic3204_tone_headphone.obj" \
"main.obj" 

C_SRCS__QUOTED += \
"../aic3204_loop_stereo_in1.c" \
"../aic3204_test.c" \
"../aic3204_tone_headphone.c" \
"../main.c" 


# Each subdirectory must supply rules for building sources it contributes
aic3204_loop_stereo_in1.obj: ../aic3204_loop_stereo_in1.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g -O3 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="..\..\..\include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large -k --asm_listing --preproc_with_compile --preproc_dependency="aic3204_loop_stereo_in1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_test.obj: ../aic3204_test.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g -O3 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="..\..\..\include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large -k --asm_listing --preproc_with_compile --preproc_dependency="aic3204_test.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_tone_headphone.obj: ../aic3204_tone_headphone.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g -O3 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="..\..\..\include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large -k --asm_listing --preproc_with_compile --preproc_dependency="aic3204_tone_headphone.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g -O3 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="..\..\..\include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large -k --asm_listing --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


