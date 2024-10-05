################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-555091761:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-555091761-inproc

build-555091761-inproc: ../Btn_long.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirtos_msp43x_2_20_00_06/packages;C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages;C:/ti/tirtos_msp43x_2_20_00_06/products/tidrivers_msp43x_2_20_00_08/packages;C:/ti/tirtos_msp43x_2_20_00_06/products/uia_2_00_06_52/packages;" xdc.tools.configuro -o configPkg -t ti.targets.msp430.elf.MSP430X -p ti.platforms.msp430:MSP430FR6989 -r release -c "C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-msp430_16.9.11.LTS" --compileOptions "-vmspx --data_model=restricted --use_hw_mpy=F5 --include_path=\"C:/ti/ccs1250/ccs/ccs_base/msp430/include\" --include_path=\"D:/SVN_Cours_TPS_2023_24/Project/SME/Btn_Lon_prj\" --include_path=\"D:/SVN_Cours_TPS_2023_24/Project/SME/Btn_Lon_prj\" --include_path=\"C:/ti/tirtos_msp43x_2_20_00_06/products/msp430_driverlib_2_70_01_01a/driverlib/MSP430FR5xx_6xx\" --include_path=\"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-msp430_16.9.11.LTS/include\" --advice:power=all --advice:power_severity=suppress --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE --define=ccs --define=MSP430WARE -g --printf_support=minimal --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-555091761 ../Btn_long.cfg
configPkg/compiler.opt: build-555091761
configPkg/: build-555091761

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-msp430_16.9.11.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccs1250/ccs/ccs_base/msp430/include" --include_path="D:/SVN_Cours_TPS_2023_24/Project/SME/Btn_Lon_prj" --include_path="D:/SVN_Cours_TPS_2023_24/Project/SME/Btn_Lon_prj" --include_path="C:/ti/tirtos_msp43x_2_20_00_06/products/msp430_driverlib_2_70_01_01a/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-msp430_16.9.11.LTS/include" --advice:power=all --advice:power_severity=suppress --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE --define=ccs --define=MSP430WARE -g --printf_support=minimal --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


