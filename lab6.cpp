/*Marshal Lindsay
 *14211662
 *ECE32220
 *Lab6, Introduction to C++ and Classes
*/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define DEFAULT_DATA_FILE "defaultData.txt"

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
		~Signal();

};

Signal::~Signal(){
	
	delete [] data;
	if(data == NULL){
		cout<<"Data deletion success"<<endl;
	}
	
}

Signal::Signal(){
	
	fstream dataFile;
	int buffer, i;
	
	dataFile.open(DEFAULT_DATA_FILE);
	
	if(!dataFile.is_open()){
		cout<<"\nCould not open "<<DEFAULT_DATA_FILE<<" setting default values!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	dataFile >> length; //Read number of integers in the datafile
	
	data = new double[length];
	if(data == NULL){
		cout<<"Could not allocate memory for data in default constructor!"
			<<"setting default values and exiting!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	dataFile >> max_value; //Read the max value of the data
	
	for(i = 0; length; i++){
		dataFile >> data[i];
	}
	
	
	dataFile.close();
	return;
}

Signal::Signal(int L){
	cout<<"FileNumber Constructor!"<<endl;
	length = 0;
	max_value = 0;
	average = 0;
	data = NULL;
}

Signal::Signal(char* fileName){
	cout<<"FileName Constructor!"<<endl;
	length = 0;
	max_value = 0;
	average = 0;
	data = NULL;
	
}


void setFileName(string*, char**);


int main(int argc, char** argv){
	double* data;
	fstream dataFile;
	
	int userInput1;
	char userInput2;
	char fileName[25];

	
	cout<<"\n****Lab6****"<<endl;
	while(1){
		
		cout<<"\nWould you like to use the default data file?(Y N)"<<endl;
		cin >> userInput2;
		while( userInput2 != 'y' &&
			userInput2 != 'Y' &&
			userInput2 != 'n' &&
			userInput2 != 'N')
			{
				cout<<"\nInvalid input!"<<endl;
				cout<<"\nWould you like to use the default data file?(Y N)"<<endl;
				cin >> userInput2;
				
			}
			
		if(userInput2 == 'Y' || userInput2 == 'y'){
			cout<<"\nUsing the default constructor"<<endl;
			Signal dataSignal;
		}else{
			cout<<"\nNot using default constructor"<<endl;
			cout<<"\nEnter 'f' to use the file name or 'n' to use the file number:"<<endl;
			cin >> userInput2;
			
			while( userInput2 != 'n' &&
			userInput2 != 'N' &&
			userInput2 != 'f' &&
			userInput2 != 'F')
			{
				cout<<"\nInvalid input!"<<endl;
				cout<<"\nEnter 'f' to use the file name or 'n' to use the file number:"<<endl;
				cin >> userInput2;
				
			}
			
			if(userInput2 == 'f'|| userInput2 == 'F'){
				cout<<"\nPlease enter the file name to be opened:"<<endl;
				cin >> fileName;
				Signal dataSignal(fileName);
			}else{
				cout<<"\nPlease enter the file number to be opened:"<<endl;
				cin >> userInput1;
				Signal dataSignal(userInput1);
			}
		}
		
		
		
		
		
	}
	

	
return(0);
}

void setFileName(string* strp, char* value){
	
	
}









