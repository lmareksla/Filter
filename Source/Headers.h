#include "PreComp.cpp"

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

	#include "/run/media/lukasm/74C5DAE971A67238/Soubory/Programy/Vlastni/c++/aplikace/advacam/Processing/SigVec/Source/INI_File.h"
	#include "/run/media/lukasm/74C5DAE971A67238/Soubory/Programy/Vlastni/c++/aplikace/advacam/Processing/SigVec/Source/GenFunc.h"


//LIB FOR WORK WITH FILES IN LINUX
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//ROOT LIBRARIES

#if !NOT_ROOT_USE
#define UNIX_ROOT_HEAD

	#include "TH2.h"
	#include "TH1.h"
	#include "TFile.h"
	#include "TTree.h"
	#include "TChain.h"
	#include "TBranch.h"
	#include "TCanvas.h"
	#include "TPad.h"
	#include "TObject.h"
	#include "TObjArray.h"
	#include "TMath.h"
	#include "TLegend.h"
	#include "TLatex.h"
	#include "TStyle.h"
	#include "TPaletteAxis.h"
	#include "TSystem.h"
	#include "THStack.h"
	#include "TPaveText.h"
	#include "TDirectory.h"
	#include "TMultiGraph.h"
	#include "TH3.h"
	#include "TPolyLine3D.h"
	#include <TGraph.h>
	#include <TGraphErrors.h>
	#include <TGraphMultiErrors.h>
	#include <TGraph2D.h>
	#include "TGraph2DErrors.h"
	//#include "TGraph2DMultiErrors.h"
	#include "TRandom.h"
	#include "TColor.h"
	#include "TMathText.h"
	#include "TDatime.h"
	#include "TF1.h"

#endif


#if defined(unix) || defined(__unix__) || defined(__unix)
	#ifndef DIR_SLASH
		#define DIR_SLASH "/"
	#else 
		#undef DIR_SLASH
		#define DIR_SLASH "/"
	#endif
#else
	#ifndef DIR_SLASH
		#define DIR_SLASH "\\"
	#else
		#undef DIR_SLASH
		#define DIR_SLASH "\\"
	#endif
#endif
