#include "Headers.h"

using namespace std;

#ifndef CLASS_Filter
#define CLASS_Filter


struct FilterElement
{
	/*FilterElement()
	{
		UpEdge = -1e300;
		DownEdge = 1e300;
	}

	~FilterElement(){}*/

	double UpEdge;
	double DownEdge;
};

struct FilterChain
{
	FilterChain()
	{
		Name = "";
	}

	~FilterChain(){;}

	string Name;
	std::vector<FilterElement> v_FilterElement;

	void Print()
	{
		printf("-------\n");
		printf("%s\n", Name.c_str() );
		for (unsigned int i = 0; i < v_FilterElement.size(); ++i)
		{
			printf("[%f,%f]", v_FilterElement[i].DownEdge, v_FilterElement[i].UpEdge );
		}
		printf("\n-------\n");
		return;
	}
};


class Filter
{
public:

	//===================================================================================
	//DESTRUCTOR, CUNTRUCTOR and INIT FUNC
	//===================================================================================


		Filter()
		{
			Init();
			Init_PrintOut_Log();

			//FileConfig = new INI_File(con_FileConfig_Path, con_FileConfig_Name);
			//Load_Config();
		}

		Filter(string con_FileConfig_Path, string con_FileConfig_Name, bool DoStanAlone = true)
		{
			Init();
			if(DoStanAlone)Init_PrintOut_Log();

			FileConfig = new INI_File(con_FileConfig_Path, con_FileConfig_Name);
			Load_Config();
		}


		void Init()
		{

			//CONFIG FILE

				FileConfig = nullptr;

			//INIT FILE IN PATH AND NAME - FOR CHECKS

				FileIn_Name = "";
				FileIn_Path = "./";

				FileOut_Name = "";
				FileOut_Path = "./";

			//EXPORT

				DoneExport = false;

			//FILTER

				//NMaxFilterChain = 50;

				//for (int i = 0; i < NMaxFilterChain; ++i) v_FilterChain.push_back(FilterElement);

				v_FilterChain = {};

				DoOR = false;

			return;
		}

		void Init_PrintOut_Log()
		{
			DoPrintOut = true;
			DoLog = true;
			FileLog = new fstream("LogFile.txt" , ios_base::out);
		}

		~Filter()
		{
			if(FileLog != nullptr && FileLog->is_open())
			{
				FileLog->close();
				delete FileLog;
			}
			Delete_CheckNull(FileConfig);
		}
		
	//===================================================================================
	//INPUT VARIABLES
	//===================================================================================
	
		string FileIn_Path;
		string FileIn_Name;

	//===================================================================================
	//
	//===================================================================================
	

	//===================================================================================
	//FILTER
	//===================================================================================

		std::vector<FilterChain> v_FilterChain;
		bool DoOR;
		//int NMaxFilterChain;

		void AddFilter(double DownEdge, double UpEdge, int Position);
		void AddFilter(double DownEdge, double UpEdge, string Name);

		//ADD SHOULD ALSO INCLUDE A CHECK ON OVERLAPS AND ORDER - SMALLER TO BIGGER

			
			bool IndivCheck(double Var, FilterElement o_FilterElement)
			{
				//printf("\tChecking indiv filter:\t%f,\t%f|%f\n", Var, o_FilterElement.DownEdge, o_FilterElement.UpEdge );
				if(Var < o_FilterElement.DownEdge || Var > o_FilterElement.UpEdge) return false;
				return true;
			}

		template<class T> bool FilterPass(std::vector<T> v_VarIn)
		{
			int MaxSize = (v_VarIn.size() > v_FilterChain.size()) ? v_FilterChain.size() : v_VarIn.size();
			bool Pass = true;

			for (int i = 0; i < MaxSize; ++i)
			{	
				for (unsigned int j = 0; j < v_FilterChain[i].v_FilterElement.size(); ++j)
				{
					Pass = IndivCheck(static_cast<double> (v_VarIn[i]), v_FilterChain[i].v_FilterElement[j]);
					if(DoOR && Pass) 	{return true;}
					if(!DoOR && Pass) 	{break;}
				}
				if(!DoOR && !Pass) 	{return false;}
			}

			if(DoOR) return false;
			return true;
		}

		void Reset();


	//===================================================================================
	//CONFIG
	//===================================================================================
	
		INI_File* FileConfig;

		string FileConfig_Path;
		string FileConfig_Name;

	 	void Load_Config();

	//===================================================================================
	//EXPORT/OUTPUT
	//===================================================================================;
	
	 	bool DoneExport;

		string FileOut_Path;
		string FileOut_Name;
		string FileOut_EndData;
		string FileOut_EndInfo;

		void Export(int Index = 0, bool DoPlot = true);

	//===================================================================================
	//PRINT and LOG
	//===================================================================================
	
		bool DoPrintOut;

		void Print_MainTitle();
		void Print_BasicInfo();

		void Print();

		bool DoLog;
		fstream *FileLog;


	//===================================================================================
	//SET AND GET FUCTIONS
	//===================================================================================
		
		void Set_FileIn_Name(string set_FileIn_Name){FileIn_Name = set_FileIn_Name; return;}
		void Set_FileIn_Path(string set_FileIn_Path){FileIn_Path = set_FileIn_Path; return;}

		void Set_FileOut_Path(string set_FileOut_Path){FileOut_Path = set_FileOut_Path;return;}
		void Set_FileOut_Name(string set_FileOut_Name){FileOut_Name = set_FileOut_Name; return;}

		void Set_DoPrintOut(bool set_DoPrintOut){DoPrintOut = set_DoPrintOut; return;}
		void Set_DoLog(bool set_DoLog){DoLog = set_DoLog; return;}
		void Set_FileLog(fstream* set_FileLog){ FileLog = set_FileLog; return;}

	//===================================================================================
	
};

#endif