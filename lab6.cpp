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
	private:
		string fileName;
		int length;
		double max_value;
		double average;
		double* data;
		
	public:
		void calcAvg();
		void scale(double);
		void offset(double);
		void center();
		void normalize();
		void Sig_info();
		void Save_file(string);
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
	this->fileName = DEFAULT_DATA_FILE;
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
	
	this->fileName = fileName;
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
	this->fileName = fileName;
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

void Signal::calcAvg(){
	double total = 0;
	int i;
	for(i = 0; i < this->length; i++){
		total += data[i];
	}
	this->average = (double)(total) / this->length;
	return;
}

void Signal::scale(double scaledValue){
	int i;
	this->max_value *= scaledValue;
	
	for(i = 0; i < this->length; i++){
		this->data[i] *= scaledValue;
	}
	calcAvg();
	
	return;
}

void Signal::offset(double offsetValue){
	int i;
	this->max_value += offsetValue;
	
	for(i = 0; i < this->length; i++){
		this->data[i] += offsetValue;
	}
	calcAvg();
	
	return;
}

void Signal::center(){
	int i;
	this->max_value -= this->average;
	for(i = 0; i < this->length; i++){
		this->data[i] -= this->average;
	}
	calcAvg();
	return;
}

void Signal::normalize(){
	int i;
	this->max_value /= this->max_value;
	for(i = 0; i < this->length; i++){
		this->data[i] /= this->max_value;
	}
	calcAvg();
	return;
}

void Signal::Sig_info(){
	
}
void Signal::Save_file(string newFileName){
}

/*FUNCTIONS*/
void optionMenu();
void helpMenu();


int main(int argc, char** argv){
	Signal* dataSignal;
	double value;
	int userInput1;
	char userInput2;
	char fileName[25];
	string newFileName;
	const char* newFilePtr = newFileName.c_str();

	
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
	
	//Set a known value for the userInput2
	userInput2 = 'p';
	//Data manipultion loop
	while(1){
		//Print the option Menu
		optionMenu();
		//Grab user input
		cin>> userInput2;
		//Convert input to uppercase
		if(islower(userInput2)){
			userInput2 = toupper(userInput2);
		}
		//Switch input and call appropriate functions
		value = 1;
		switch(userInput2){
		case 'S':
			dataSignal->scale(value);
			break;
		case 'O':
			dataSignal->offset(value);
			break;
		case 'P':
			dataSignal->Sig_info();
			break;
		case 'C':
			dataSignal->center();
			break;
		case 'N':
			dataSignal->normalize();
			break;
		case 'V':
			dataSignal->Save_file(newFilePtr);
			break;
		case 'Q':
			break;
		default:
			cout<<"Invalid input!"<<endl;
			break;
		}
		
		if(userInput2 == 'Q'){
			break;
		}
	
	}
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

void optionMenu(){
	
	cout<<"What would you like to do with the signal?"<<endl;
	cout<<"(S) : Scale the data\n"
		<<"(O) : Offset the data\n"
		<<"(P) : Print statistics for the data\n"
		<<"(C) : Center the data\n"
		<<"(N) : Normalize the data\n"
		<<"(V) : Save data to file\n"
		<<"(Q) : Quit"<<endl;
	return;
}

void helpMenu(){
	cout<<"\n****************HELP MESSAGE****************"<<endl;

	
	return;
}

/*
void scale(Signal* dataSignal){
	double scaleValue;
	int i;
	string newFileName = std::string("Scaled_") + dataSignal->fileName;
	const char* fileNamePointer = newFileName.c_str();
	ofstream outputFile(fileNamePointer);
	
	//Check that the file was opened
	if(!outputFile.is_open()){
		cout<<"Could not open "<<newFileName<<"! Quitting Scale!"<<endl;
		return;
	}
	
	cout<<"Please enter the value you wish to scale the data by:"<<endl;
	cin >> scaleValue;
	
	//Check that the user input is a double type
	while(cin.fail()){
		cin.clear();
		fflush(stdin);
		cout<<"Invalid input! Please enter a number!"<<endl;
		cin >> scaleValue;
	}
	
	//Print the length, max_value, length and updated max_value to the output file
	outputFile << dataSignal->length
				<< " "<<dataSignal->max_value;
	outputFile <<"\t\t\t"<<dataSignal->length<<" "<<(dataSignal->max_value)*scaleValue<<endl;
	
	//Print the data and the scaled data to the output file
	for(i = 0; i < dataSignal->length; i++){
		outputFile<<dataSignal->data[i]<<"\t\t\t"<<(dataSignal->data[i])*scaleValue<<endl;
	}
	
	//Close the file
	outputFile.close();
	
	return;
	
	
}

void offset(Signal* dataSignal){
	double offsetValue;
	int i;
	string newFileName = std::string("Offset_") + dataSignal->fileName;
	const char* fileNamePointer = newFileName.c_str();
	ofstream outputFile(fileNamePointer);
	
	//Check that the file was opened
	if(!outputFile.is_open()){
		cout<<"Could not open "<<newFileName<<"! Quitting Offset!"<<endl;
		return;
	}
	
	cout<<"Please enter the value you wish to offset the data by:"<<endl;
	cin >> offsetValue;
	
	//Check that the user input is a double type
	while(cin.fail()){
		cin.clear();
		fflush(stdin);
		cout<<"Invalid input! Please enter a number!"<<endl;
		cin >> offsetValue;
	}
	
	//Print the length, max_value, length and updated max_value to the output file
	outputFile << dataSignal->length
				<< " "<<dataSignal->max_value;
	outputFile <<"\t\t\t"<<dataSignal->length<<" "<<(dataSignal->max_value)+offsetValue<<endl;
	
	//Print the data and the offset data to the output file
	for(i = 0; i < dataSignal->length; i++){
		outputFile<<dataSignal->data[i]<<"\t\t\t"<<(dataSignal->data[i])+offsetValue<<endl;
	}
	
	//Close the file
	outputFile.close();
	
	return;
}
void rename(Signal* dataSignal){
	int i;
	string newFileName;
	const char* fileNamePointer = newFileName.c_str();
	
	cout<<"Please enter the new file name:"<<endl;
	cin >> newFileName;
	
	newFileName += ".txt";
	
	ofstream outputFile(fileNamePointer);
	
	if(!outputFile.is_open()){
		cout<<"Could not open "<<newFileName<<"! Quitting Rename!"<<endl;
		return;
	}
	
	//Print the length and the max_value to the new file
	outputFile << dataSignal->length
				<< " "<<dataSignal->max_value<<endl;
	
	//Print the data to the new file
	for(i = 0; i < dataSignal->length; i++){
		outputFile<<dataSignal->data[i]<<endl;
	}
	
	//Close the file
	outputFile.close();
	
	return;
	
}
void statistics(Signal* dataSignal){
	
}
void center(Signal* dataSignal){
	
}
void normalize(Signal* dataSignal){
	
}
*/



