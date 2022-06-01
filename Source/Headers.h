#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "INI_File.h"
#include "GenFunc.h"


//LIB FOR WORK WITH FILES IN LINUX
#if defined(unix) || defined(__unix__) || defined(__unix)
	#include <unistd.h>
	#include <dirent.h>
#else
	#include <dirent_win.h>
	#include <direct.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>


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
