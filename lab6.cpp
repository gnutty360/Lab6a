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
//Signal Class
class Signal{
	public:
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
//Destructor
Signal::~Signal(){
	
	cout<<"Destructor"<<endl;
	delete [] data;

}
//Default Constructor
Signal::Signal(){
	
	fstream dataFile;
	int i;
	
	//Open the default data file
	dataFile.open(DEFAULT_DATA_FILE);
	
	//Check that the file was opened correctly.
	//If not, set default values and return
	if(!dataFile.is_open()){
		cout<<"\nCould not open "<<DEFAULT_DATA_FILE<<" setting default values!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Read the number of integers in the datafile
	dataFile >> length;
	
	//Allocate memory for the data array.
	data = new double[length];
	
	//Check that data was allocated correctly.
	//If it wasn't, set default values and quit.
	if(data == NULL){
		cout<<"Could not allocate memory for data in default constructor!"
			<<"setting default values and exiting!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Read the max value from the data file
	dataFile >> max_value;
	
	//Read the data from the file and place in the data array.
	for(i = 0; i < length; i++){
		dataFile >> data[i];
	}
	
	//Close the data file. 
	dataFile.close();
	return;
}
//Integer Input Constructor
Signal::Signal(int L){
	fstream dataFile;
	int i;
	char ones, tens;
	string fileName;
	
	//Declare a const char* to be used with the .open() on line 115
	//that points to the file name.
	const char* ptrFileName = fileName.c_str();
	
	
	//Convert the integer L to 2 chacters to be appended to a string
	if(L < 10){
		ones = L + 48;
		tens = 48;
	}else if(L > 10 && L < 100){
		ones = L % 10 + 48;
		tens = L / 10 + 48;
	}else{
		cout<<"\nInvalid file number! Setting default values and quitting!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Append the converted integers into the file name template
	fileName = std::string("Raw_data_") + tens + ones + ".txt";
	
	//Open the correct file
	dataFile.open(ptrFileName);
	
	//Check that the file was opened correctly.
	//If not, set default values and return
	if(!dataFile.is_open()){
		cout<<"\nCould not open "<<fileName<<" setting default values!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Read the number of integers in the datafile
	dataFile >> length;
	
	//Allocate memory for the data array.
	data = new double[length];
	
	//Check that data was allocated correctly.
	//If it wasn't, set default values and quit.
	if(data == NULL){
		cout<<"Could not allocate memory for data in default constructor!"
			<<"setting default values and exiting!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Read the max value from the data file
	dataFile >> max_value;
	
	//Read the data from the file and place in the data array.
	for(i = 0; i < length; i++){
		dataFile >> data[i];
	}
	
	dataFile.close();
	return;
}
//Char* constructor
Signal::Signal(char* fileName){
	fstream dataFile;
	int i;
	
	//Open the data file
	dataFile.open(fileName);
	
	//Check that the file was opened correctly.
	//If not, set default values and return
	if(!dataFile.is_open()){
		cout<<"\nCould not open "<<fileName<<" setting default values!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Read the number of integers in the datafile
	dataFile >> length;
	
	//Allocate memory for the data array.
	data = new double[length];
	
	//Check that data was allocated correctly.
	//If it wasn't, set default values and quit.
	if(data == NULL){
		cout<<"Could not allocate memory for data in default constructor!"
			<<"setting default values and exiting!"<<endl;
		length = 0;
		max_value = 0;
		average = 0;
		data = NULL;
		return;
	}
	
	//Read the max value from the data file
	dataFile >> max_value;
	
	//Read the data from the file and place in the data array.
	for(i = 0; i < length; i++){
		dataFile >> data[i];
	}
	
	//Close the data file. 
	dataFile.close();
	return;

}



int main(int argc, char** argv){
	Signal* dataSignal;
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
			dataSignal = new Signal;
		}else{
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
				cout<<"Please enter the file name to be opened:"<<endl;
				cin >> fileName;
				dataSignal = new Signal(fileName);
			}else{
				cout<<"\nPlease enter the file number to be opened:"<<endl;
				cin >> userInput1;
				dataSignal = new Signal(userInput1);
			}
		}
		
		
	//Data manipulation here


	
	cout<<"Would you like to manipulate another signal?(Y N)"<<endl;
	cin >> userInput2;
	while( userInput2 != 'y' && userInput2 != 'Y' && userInput2 != 'n' && userInput2 != 'N'){
			cout<<"\nInvalid input!"<<endl;
			cout<<"Would you like to manipulate another signal?(Y N)"<<endl;
			cin >> userInput2;			
		}
	if(userInput2 == 'n' || userInput2 == 'N'){
		delete dataSignal;
		break;
		}
		
		
	
	}
return(0);
}









