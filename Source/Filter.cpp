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



	void Filter::Print()
	{
		string PrintOut = "\n";

		PrintOut +="===========================================================\n";
		PrintOut +="FILTER\n";
		PrintOut +="\n";
		if(DoOR) 	PrintOut +="Conditions are logically conected as OR for different elements (within as AND)\n";
		else		PrintOut +="Conditions are logically conected as AND for different elements (within as AND)\n";
		PrintOut +="\n";
		PrintOut +="\tIndex\tCond.\n";

		for (unsigned int i = 0; i < v_FilterChain.size(); ++i)
		{
			if(v_FilterChain[i].v_FilterElement.size() != 0)
			{
				PrintOut +="\t" + to_string(i);

				if(v_FilterChain[i].Name.size() != 0) PrintOut += "|" + v_FilterChain[i].Name ;
				
				PrintOut +="\n";

				for (unsigned int j = 0; j < v_FilterChain[i].v_FilterElement.size(); ++j)
				{
					PrintOut +="\t\t[" + to_string(v_FilterChain[i].v_FilterElement[j].DownEdge)  + "|" + to_string(v_FilterChain[i].v_FilterElement[j].UpEdge) + "]\n";
				}
			}
		}

		PrintOut +="===========================================================\n";

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
		//FileConfig->Print();

		/*
		//INPUT

			if(FileConfig->IsParInSection("FileIn_Path","Input")) 		FileIn_Path = FileConfig->FindParInSection("FileIn_Path", "Input").v_ValStr[0];
			if(FileConfig->IsParInSection("FileIn_Name","Input")) 		FileIn_Name = FileConfig->FindParInSection("FileIn_Name", "Input").v_ValStr[0];

		//OUTPUT

			if(FileConfig->IsParInSection("FileOut_Path","Output")) 	FileOut_Path = FileConfig->FindParInSection("FileOut_Path", "Output").v_ValStr[0];
			if(FileConfig->IsParInSection("FileOut_Name","Output")) 	FileOut_Name = FileConfig->FindParInSection("FileOut_Name", "Output").v_ValStr[0];
			
		*/

		//MAIN SETTINGS

			for (unsigned int i = 0; i < FileConfig->v_Section.size(); ++i)
			{
				Section* o_Section = FileConfig->v_Section[i];

				string FilterName = o_Section->KeyName;

				for (unsigned int j = 0; j < o_Section->v_Par.size(); ++j)
				{
					Par o_Par = o_Section->v_Par[j];

					if(o_Par.v_ValNum.size() >= 2)
					{
						double UpEdge = o_Par.v_ValNum[1];
						double DownEdge =  o_Par.v_ValNum[0];	

						AddFilter(DownEdge, UpEdge, FilterName);
					}
				}
			}

		return;
	}


//===================================================================================
//FILTER
//===================================================================================


	void Filter::AddFilter(double DownEdge, double UpEdge, int Position)
	{
		//printf("-------\n");
		//printf("Add filter: %f, %f, %d\n", DownEdge, UpEdge, Position );

		//BASIC CHECK ON POSITION adn DOWN AND UP EDGE

			if(Position < 0 || UpEdge < DownEdge) {printf("[ERROR]\tAdd filter failed!\n"); return;}

		//ADD FILTER CHAIN IF SIZE OF FILTER IS TOO SMALL

			//cout << v_FilterChain.size() << endl;
			//cout << Position << endl;

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

			//printf("Add filter done\n");

		return;
	}

	void Filter::AddFilter(double DownEdge, double UpEdge, string Name)
	{
		//BASIC CHECK ON POSITION adn DOWN AND UP EDGE

			if(UpEdge < DownEdge || Name.size() == 0) {printf("[ERROR]\tAdd filter failed!\n"); return;}

		FilterElement o_FilterElement;
		o_FilterElement.DownEdge = DownEdge;
		o_FilterElement.UpEdge = UpEdge;

		//ADD

			for (unsigned int i = 0; i < v_FilterChain.size(); ++i)
			{
				if(!Name.compare(v_FilterChain[i].Name))
				{
					v_FilterChain[i].v_FilterElement.push_back(o_FilterElement);
					return;					
				}
			}

		//IF NO MATCH -> CREATE NEW CHAIN

			FilterChain o_FilterChain;
			o_FilterChain.Name = Name;
			o_FilterChain.v_FilterElement.push_back(o_FilterElement);

			v_FilterChain.push_back(o_FilterChain);

		return;

	}

	void Filter::Reset()
	{
		v_FilterChain.clear();
		return;
	}


//===================================================================================
//SUPPORT FUCTIONS
//===================================================================================


//===================================================================================
	

#endif