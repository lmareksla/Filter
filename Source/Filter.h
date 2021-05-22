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
	std::vector<FilterElement> v_FilterElement;
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

		Filter(string con_FileConfig_Path, string con_FileConfig_Name)
		{
			Init();
			Init_PrintOut_Log();

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
			Delete_CheckNull(FileLog);
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

			
			bool IndivCheck(double Var, FilterElement o_FilterElement)
			{
				printf("\tChecking indiv filter:\t%f,\t%f|%f\n", Var, o_FilterElement.DownEdge, o_FilterElement.UpEdge );
				if(Var < o_FilterElement.DownEdge || Var > o_FilterElement.UpEdge) return false;
				return true;
			}

		template<class T> bool FilterPass(std::vector<T> v_VarIn)
		{
			printf("------------------------------\n");
			printf("Check filter pass\n");
			printf("\n");

			int MaxSize = (v_VarIn.size() > v_FilterChain.size()) ? v_FilterChain.size() : v_VarIn.size();
			bool Pass = true;

			cout << "MaxSize:\t" << MaxSize << endl;

			for (int i = 0; i < MaxSize; ++i)
			{	
				for (unsigned int j = 0; j < v_FilterChain[i].v_FilterElement.size(); ++j)
				{
					cout << "\t" << i << "\t" << j << endl;

					Pass = IndivCheck(static_cast<double> (v_VarIn[i]), v_FilterChain[i].v_FilterElement[j]);
					if(Pass) printf("\tIndiv filter passed\n");
					if(DoOR && Pass) 	{printf("Whole filter passed - OR\n");return true;}
					if(!DoOR && !Pass) 	{printf("Whole filter not passed - AND\n");return false;}
				}
			}

			if(DoOR) return false;
			return true;
		}


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

		bool DoLog;
		fstream *FileLog;

		void Print();

	//===================================================================================
	//SET AND GET FUCTIONS
	//===================================================================================
		
		void Set_FileIn_Name(string set_FileIn_Name){FileIn_Name = set_FileIn_Name; return;}
		void Set_FileIn_Path(string set_FileIn_Path){FileIn_Path = set_FileIn_Path; return;}

		void Set_FileOut_Path(string set_FileOut_Path){FileOut_Path = set_FileOut_Path;return;}
		void Set_FileOut_Name(string set_FileOut_Name){FileOut_Name = set_FileOut_Name; return;}

		void Set_DoPrintOut(bool set_DoPrintOut){DoPrintOut = set_DoPrintOut; return;}
		void Set_DoLog(bool set_DoLog){DoLog = set_DoLog; return;}
		
	//===================================================================================
	
};

#endif