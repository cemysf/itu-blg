################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
../452_Labs_Essentials.lib \
../55xdspx_LARGE.lib \
../rts55x.lib \
../usbstk5515bsl.lib 

C_SRCS += \
../AIC_func.c \
../LCD_FCN.c \
../main.c \
../sar.c \
../usbstk5515.c \
../usbstk5515_gpio.c \
../usbstk5515_i2c.c \
../usbstk5515_led.c 

CMD_SRCS += \
../C5515CMDFILE.cmd 

OBJS += \
./AIC_func.obj \
./LCD_FCN.obj \
./main.obj \
./sar.obj \
./usbstk5515.obj \
./usbstk5515_gpio.obj \
./usbstk5515_i2c.obj \
./usbstk5515_led.obj 

C_DEPS += \
./AIC_func.pp \
./LCD_FCN.pp \
./main.pp \
./sar.pp \
./usbstk5515.pp \
./usbstk5515_gpio.pp \
./usbstk5515_i2c.pp \
./usbstk5515_led.pp 

C_DEPS__QUOTED += \
"AIC_func.pp" \
"LCD_FCN.pp" \
"main.pp" \
"sar.pp" \
"usbstk5515.pp" \
"usbstk5515_gpio.pp" \
"usbstk5515_i2c.pp" \
"usbstk5515_led.pp" 

OBJS__QUOTED += \
"AIC_func.obj" \
"LCD_FCN.obj" \
"main.obj" \
"sar.obj" \
"usbstk5515.obj" \
"usbstk5515_gpio.obj" \
"usbstk5515_i2c.obj" \
"usbstk5515_led.obj" 

C_SRCS__QUOTED += \
"../AIC_func.c" \
"../LCD_FCN.c" \
"../main.c" \
"../sar.c" \
"../usbstk5515.c" \
"../usbstk5515_gpio.c" \
"../usbstk5515_i2c.c" \
"../usbstk5515_led.c" 


# Each subdirectory must supply rules for building sources it contributes
AIC_func.obj: ../AIC_func.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="AIC_func.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LCD_FCN.obj: ../LCD_FCN.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="LCD_FCN.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sar.obj: ../sar.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="sar.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5515.obj: ../usbstk5515.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="usbstk5515.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5515_gpio.obj: ../usbstk5515_gpio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="usbstk5515_gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5515_i2c.obj: ../usbstk5515_i2c.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="usbstk5515_i2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5515_led.obj: ../usbstk5515_led.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c5500/include" --include_path="C:\Documents and Settings\GSI\workspace\452_Support" --diag_warning=225 --ptrdiff_size=32 --memory_model=huge --preproc_with_compile --preproc_dependency="usbstk5515_led.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


