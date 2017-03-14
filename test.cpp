#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(void){

	ofstream file("newfile.txt");
	if(file.is_open()){
		cout<<"file is open"<<endl;
	}
	file<<"nothing new"<< endl;
	file.close();
	return(0);
}