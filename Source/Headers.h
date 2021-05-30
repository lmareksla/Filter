
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

#ifndef NOT_ROOT_USE
#define NOT_ROOT_USE true
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
