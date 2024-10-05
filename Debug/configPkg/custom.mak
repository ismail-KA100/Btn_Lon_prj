## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e430X linker.cmd package/cfg/Btn_long_pe430X.oe430X

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/Btn_long_pe430X.xdl
	$(SED) 's"^\"\(package/cfg/Btn_long_pe430Xcfg.cmd\)\"$""\"D:/SVN_Cours_TPS_2023_24/Project/SME/Btn_Lon_prj/Debug/configPkg/\1\""' package/cfg/Btn_long_pe430X.xdl > $@
	-$(SETDATE) -r:max package/cfg/Btn_long_pe430X.h compiler.opt compiler.opt.defs
