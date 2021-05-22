#include "Filter.h"

using namespace std;


#ifndef CLASS_Filter_FUNC
#define CLASS_Filter_FUNC


//===================================================================================
//PRINT and LOG
//===================================================================================


	void Filter::Print_MainTitle()
	{
		string PrintOut = "";
		PrintOut = 
					PrintOut + "\n" + 
					//"-----------------------------------------------------------\n"+
					"------------     Filter    ------------\n";
					//"-----------------------------------------------------------\n";

		if (DoPrintOut) printf("%s\n", PrintOut.c_str());
		if (DoLog) *FileLog << PrintOut << endl;

		return;
	}

	void Filter::Print_BasicInfo()
	{
		string PrintOut = "\n";

		PrintOut += "FileIn_Path:\t" +   FileIn_Path+ "\n";
		PrintOut += "FileIn_Path:\t" +   FileIn_Name+ "\n";
		PrintOut += "FileOut_Path:\t" +   FileOut_Path+ "\n";
		PrintOut += "FileOut_Name:\t" +   FileOut_Name+ "\n";

		PrintOut += "\n";

		if (DoPrintOut) printf("%s\n", PrintOut.c_str());
		if (DoLog) *FileLog << PrintOut << endl;
		
		return;
	}	


//===================================================================================
//LOAD CONFIG
//===================================================================================

	void Filter::Load_Config()
	{

		FileConfig->Read();
		FileConfig->Print();

		//INPUT

			if(FileConfig->IsParInSection("FileIn_Path","Input")) 		FileIn_Path = FileConfig->FindParInSection("FileIn_Path", "Input").v_ValStr[0];
			if(FileConfig->IsParInSection("FileIn_Name","Input")) 		FileIn_Name = FileConfig->FindParInSection("FileIn_Name", "Input").v_ValStr[0];

		//OUTPUT

			if(FileConfig->IsParInSection("FileOut_Path","Output")) 	FileOut_Path = FileConfig->FindParInSection("FileOut_Path", "Output").v_ValStr[0];
			if(FileConfig->IsParInSection("FileOut_Name","Output")) 	FileOut_Name = FileConfig->FindParInSection("FileOut_Name", "Output").v_ValStr[0];
			
		//MIAN SETTINGS

			//...

		return;
	}


//===================================================================================
//FILTER
//===================================================================================


	void Filter::AddFilter(double DownEdge, double UpEdge, int Position)
	{
		printf("-------\n");
		printf("Add filter: %f, %f, %d\n", DownEdge, UpEdge, Position );

		//BASIC CHECK ON POSITION

			if(Position < 0) {printf("[ERROR]\tAdd filter failed!\n"); return;}

		//ADD FILTER CHAIN IF SIZE OF FILTER IS TOO SMALL

			cout << v_FilterChain.size() << endl;
			cout << Position << endl;

			if(Position >= v_FilterChain.size()) 
			{
				for (int i = 0; i <= Position - (int)v_FilterChain.size(); ++i)
				{
					FilterChain o_FilterChain;
					v_FilterChain.push_back(o_FilterChain);
				}
			}

		//ADD NEW ELEMENT

			FilterElement o_FilterElement;
			o_FilterElement.UpEdge = UpEdge;
			o_FilterElement.DownEdge = DownEdge;
			v_FilterChain[Position].v_FilterElement.push_back(o_FilterElement);

			printf("Add filter done\n");

		return;
	}




//===================================================================================
//SUPPORT FUCTIONS
//===================================================================================


//===================================================================================
	

#endif