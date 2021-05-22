#!/bin/bash

PATH_DF="/run/media/lukasm/74C5DAE971A67238/Soubory/Programy/Vlastni/c++/aplikace/advacam/PreProcessing/ClusterProc/Source"
#PATH_HIST_File="/run/media/lukasm/74C5DAE971A67238/Soubory/Programy/Vlastni/c++/aplikace/advacam/Processing/Hist/Source/"
PATH_SIG_VEC="/run/media/lukasm/74C5DAE971A67238/Soubory/Programy/Vlastni/c++/aplikace/advacam/Processing/SigVec/Source/"

#INIT PRECOMP

	#PID PRECOMP

	touch ../../Source/PreComp.cpp
	echo "#ifndef NOT_ROOT_USE" > '../../Source/PreComp.cpp'
	echo "#define NOT_ROOT_USE true" >> '../../Source/PreComp.cpp'
	echo "#endif" >> '../../Source/PreComp.cpp'
	
	
	#SIG VEC PRE COMP

	touch $PATH_SIG_VEC'PreComp.cpp'
	echo "#ifndef NOT_ROOT_USE" > $PATH_SIG_VEC'PreComp.cpp'
	echo "#define NOT_ROOT_USE true" >>   $PATH_SIG_VEC'PreComp.cpp'
	echo "#endif" >> $PATH_SIG_VEC'PreComp.cpp'		

#COMPILE
	
	GEN_FUNC_Compile=$PATH_SIG_VEC"GenFunc.cpp"	
	INI_FILE_Compile=$PATH_SIG_VEC"INI_File.cpp"
	#DF_Compile="$PATH_DF/Pixel.cpp $PATH_DF/Cluster.cpp $PATH_DF/ClusterAnalysis.cpp $PATH_DF/Clusterer.cpp $PATH_DF/ClusterList.cpp $PATH_DF/DataFile.cpp " 
	#HIST_Compile="$PATH_HIST_File/Hist.cpp $PATH_HIST_File/Hist1D.cpp $PATH_HIST_File/Hist2D.cpp $PATH_HIST_File/HistUse.cpp" 
	RECLUSTER_Compile="../../Source/Filter.cpp"

	if 	g++ -std=c++0x -pthread -Wall -o3 $GEN_FUNC_Compile $INI_FILE_Compile $RECLUSTER_Compile main.cpp  -o Filter -static; then
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

	echo "#ifndef NOT_ROOT_USE" > '../../Source/PreComp.cpp'
	echo "#define NOT_ROOT_USE false" >> '../../Source/PreComp.cpp'
	echo "#endif" >> '../../Source/PreComp.cpp'

	echo "#ifndef NOT_ROOT_USE" > $PATH_SIG_VEC'PreComp.cpp'
	echo "#define NOT_ROOT_USE false" >> $PATH_SIG_VEC'PreComp.cpp'
	echo "#endif" >> $PATH_SIG_VEC'PreComp.cpp'