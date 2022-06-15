#include "../../Source/Headers.h"
#include "../../Source/Filter.h"


using namespace std;



int main(int argc, char const *argv[])
{

	int Case; 
	if(argc > 1)
	{
		stringstream s(argv[1] );
		s >> Case;
	}else Case = 1;

	switch(Case) 
	{
	    case 1 : 
	    	{
			//===================================================================================
			//BASIC FUNC
			//===================================================================================

	    		printf("Basic functionality of Filter.\n");
				
	    		Filter *o_Filter = new Filter();


	    		//FILER SPECIFICATION

	    			//o_Filter->AddFilter(0,2,0);
	    			//o_Filter->AddFilter(4,5,1);
	    			//o_Filter->AddFilter(1,3,1);
	    			//o_Filter->AddFilter(1,3,10);

	    			o_Filter->AddFilter(1,3,"Energy");
	    			o_Filter->AddFilter(4,5,"Energy");	    			
	    			o_Filter->AddFilter(1,6,"Size");

	    			o_Filter->DoOR = false;

	    			o_Filter->Print();

	    		std::vector<double> v_VecTest = {1,2,3,4,6};

	    		if(o_Filter->FilterPass(v_VecTest)) printf("Filter passed\n");
	    		else 								printf("Filter has not been passed\n");


	    		delete o_Filter;

			//===================================================================================
			}
	        break;   		
	    case 2 : 
	    	{
			//===================================================================================
			//LOAD FROM CONFIG
			//===================================================================================

	    		printf("Loading from config file.\n");
				
	    		Filter *o_Filter = new Filter("./","ConfigFile.ini");

	    		o_Filter->Print();

	    		delete o_Filter;

			//===================================================================================
			}
	        break;   
	}


	return 0;
}

