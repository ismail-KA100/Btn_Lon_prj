# invoke SourceDir generated makefile for Btn_long.pe430X
Btn_long.pe430X: .libraries,Btn_long.pe430X
.libraries,Btn_long.pe430X: package/cfg/Btn_long_pe430X.xdl
	$(MAKE) -f D:\SVN_Cours_TPS_2023_24\Project\SME\Btn_Lon_prj/src/makefile.libs

clean::
	$(MAKE) -f D:\SVN_Cours_TPS_2023_24\Project\SME\Btn_Lon_prj/src/makefile.libs clean

