################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
AIC_func.obj: X:/dersnotlar/blg438e/bliky_usbstk5515/C5515_Support_Files/C5515_Lib/C-Code/AIC_func.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"X:/ccs6/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O3 -g --include_path="X:/ccs6/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/C5515_Support_Files/C5515_Includes" --include_path="X:/dersnotlar/blg438e/bliky_usbstk5515/bliky_usbstk5515/drivers" --define=DEBUG --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --algebraic --preproc_with_compile --preproc_dependency="AIC_func.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"X:/ccs6/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O3 -g --include_path="X:/ccs6/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/C5515_Support_Files/C5515_Includes" --include_path="X:/dersnotlar/blg438e/bliky_usbstk5515/bliky_usbstk5515/drivers" --define=DEBUG --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --algebraic --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5515_i2c.obj: X:/dersnotlar/blg438e/bliky_usbstk5515/C5515_Support_Files/C5515_Lib/C-Code/usbstk5515_i2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"X:/ccs6/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O3 -g --include_path="X:/ccs6/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/C5515_Support_Files/C5515_Includes" --include_path="X:/dersnotlar/blg438e/bliky_usbstk5515/bliky_usbstk5515/drivers" --define=DEBUG --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --algebraic --preproc_with_compile --preproc_dependency="usbstk5515_i2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


