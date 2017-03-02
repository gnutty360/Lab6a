/*Marshal Lindsay
 *14211662
 *ECE32220
 *Lab6, Introduction to C++ and Classes
*/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define DEFAULT_DATA_FILE "defaultData"

class Signal{
	private:
		int length;
		double max_value;
		double average;
		double* data;
	public:
		Signal();
		Signal(int);
		Signal(char*);

};

Signal::Signal(){

	

}


void setFileName(string*, char**);

int main(int argc, char** argv){
	double* data;
	fstream dataFile;

	string fileName;
	
	if(checkInputs(argc, argv)){
		cout<<endl<<"Invlaid command line arguments. Terminating!"<<endl;
	}
	
	
	
	dataFile.open(fileName);
	if(!datafile.is_open()){
		count<<endl<<"Unable to open file "<<fileName<<". Quitting."<<endl;
	}
	
	 
	
return(0);
}

void setFileName(string* strp, char* value){
	
	
}






/*
int checkInputs(int argc, char** argv){

	int i;
	string str1 = argv[1];
	if(str1.compare("-n") == 0 || str1.compare("-N") == 0){
	
		str1 = argv[2];
		i = stoi(str1);
		cout<<endl<<i<<endl;	
	
	}else if(str1.compare("-f")){

	}else{

	return(1);
	
	}
}
*/
