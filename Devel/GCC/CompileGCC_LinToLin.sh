#!/bin/bash

#PATH_HIST_File="/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/DataProcessing/Processing/Hist/Source/"
PATH_SIG_VEC="/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/DataProcessing/Processing/SigVec/Source/"

#INIT PRECOMP
	
	#SIG VEC PRE COMP

	echo $PATH_SIG_VEC'PreComp.cpp'

	touch $PATH_SIG_VEC'PreComp.cpp'
	echo "#ifndef NOT_ROOT_USE" > $PATH_SIG_VEC'PreComp.cpp'
	echo "#define NOT_ROOT_USE true" >>   $PATH_SIG_VEC'PreComp.cpp'
	echo "#endif" >> $PATH_SIG_VEC'PreComp.cpp'		

#COMPILE
	
	GEN_FUNC_Compile="/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/GenLib/Source/GenFunc.cpp"	
	INI_FILE_Compile="/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/INI_File/Source/INI_File.cpp"
	FILTER_Compile="../../Source/Filter.cpp"

	#DF_Compile="$PATH_DF/Pixel.cpp $PATH_DF/Cluster.cpp $PATH_DF/ClusterAnalysis.cpp $PATH_DF/Clusterer.cpp $PATH_DF/ClusterList.cpp $PATH_DF/DataFile.cpp " 
	#HIST_Compile="$PATH_HIST_File/Hist.cpp $PATH_HIST_File/Hist1D.cpp $PATH_HIST_File/Hist2D.cpp $PATH_HIST_File/HistUse.cpp" 

	if 	g++ -std=c++0x -pthread -Wall -o3  $GEN_FUNC_Compile $INI_FILE_Compile $FILTER_Compile main.cpp  -o Filter -static; then
		echo "================================================================"
		./Filter $1
		echo "================================================================"
		echo "End of program."; 
		echo "================================================================"
	else 
		echo "================================================================"
		echo "Failure of complilation!"; 
		echo "================================================================"		
	fi

#COPY NEEDED FILES AND THE COMPILED ONE

	#mv Hist_ProcessFile ../Build/
	#cp ../Devel/Test/SigVec/SigVec_ConfigFile.ini ../Build/

#RETURN ORIGINAL VAL TO PreComp

	echo "#ifndef NOT_ROOT_USE" > $PATH_SIG_VEC'PreComp.cpp'
	echo "#define NOT_ROOT_USE false" >> $PATH_SIG_VEC'PreComp.cpp'
	echo "#endif" >> $PATH_SIG_VEC'PreComp.cpp'