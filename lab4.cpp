/*
 * Marshall Lindsay
 * 14211662
 * Lab4
 * ECE 3220
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char**, int, int*);
void argumentDecision(char**, int, FILE*, int*);
int checkArguments(char**, int);

void scale (FILE*, double, int*);
void offset (FILE*, double, int*);
void renameFile (FILE*, char*);
void help();
void statistics(FILE*, int*);
void centerData(FILE*, int*);
void normalize(FILE*, int*);


int main(int argc, char* argv[]){

	int number;
	char check;
	int fileNumber;
	FILE* fp = NULL;


	//Makes sure all of the command line arguments are properly inputed
	//Returns error messages if they aren't.
	check = checkArguments(argv, argc);
	if(check == 3){
		help();
		return(0);
	}else if(check){
		return(1);
	}
	//Attempts to open the file. If the file does not open, or if the file number
	//isn't valid, returns NULL.
	fp = openFile(argv, argc, &fileNumber);
	
	if(fp == NULL){
		printf("\nFile could not be opened!");
		return(1);
	}
	
	argumentDecision(argv, argc, fp, &fileNumber);
	
	printf("\nClosing file!");
	if(fclose(fp) != 0){
		printf("\nFile was not close successfully!");
	}
	return(EXIT_SUCCESS);


}

FILE* openFile(char** argv, int argc, int* fileNumPtr){
	char fileName[15];
	int fileNumber;
	int i;
	
	for(i = 1; i < argc; i++){
		
		if(!strcmp(argv[i], "-n")){
			i++;
			fileNumber = atoi(argv[i]);
			*fileNumPtr = fileNumber;
		}
	}
	
	
	//I really do not like this switch statement.
	//I could probably split the string and then concatenate to make
	//more pleasent to look at. I will use this for now because I know
	//that It will work. 
	switch(fileNumber){
	case 1:
		strcpy(fileName, "Raw_data_01.txt");
		break;
	case 2:
		strcpy(fileName, "Raw_data_02.txt");
		break;
	case 3:
		strcpy(fileName, "Raw_data_03.txt");
		break;
	case 4:
		strcpy(fileName, "Raw_data_04.txt");
		break;
	case 5:
		strcpy(fileName, "Raw_data_05.txt");
		break;
	case 6:
		strcpy(fileName, "Raw_data_06.txt");
		break;
	case 7:
		strcpy(fileName, "Raw_data_07.txt");
		break;
	case 8:
		strcpy(fileName, "Raw_data_08.txt");
		break;
	case 9:
		strcpy(fileName, "Raw_data_09.txt");
		break;
	case 10:
		strcpy(fileName, "Raw_data_10.txt");
		break;
	case 11:
		strcpy(fileName, "Raw_data_11.txt");
		break;
	default:
		printf("\nInvalid file number!");
		return(NULL);

	}
		
	printf("\nOpening %s...", fileName);
	FILE* fp = fopen(fileName, "r");
	
	if(fp == NULL){
		printf("\nError opening %s\nTerminating", fileName);
	}
	return(fp);
}

int checkArguments(char** argv, int argc){
	int i;
	char file = 0;
	double number;
	for(i = 1; i < argc; i++){
		
		if(!strcmp(argv[i], "-s")){
			i++;
			number = atof(argv[i]);
			if(number == 0){
				printf("\nArgument %d:'%s' is invalid! Use '-h' for options", i, argv[i]);
				return(1);
			}
				
		}else if(!strcmp(argv[i], "-n")){
			i++;
			file++;
			number = atof(argv[i]);
			if(number == 0){
				printf("\nArgument %d:'%s' is invalid! Use '-h' for options", i, argv[i]);
				return(1);
			}
		}else if(!strcmp(argv[i], "-o")){
			i++;
			number = atof(argv[i]);
			if(number == 0){
				printf("\nArgument %d:'%s' is invalid! Use '-h' for options", i, argv[i]);
				return(1);
			}
		}else if(!strcmp(argv[i], "-r")){
			i++;
		}else if(!strcmp(argv[i], "-h")){
			return(3);
		}else if(!strcmp(argv[i], "-S")){
		}else if(!strcmp(argv[i], "-C")){
		}else if(!strcmp(argv[i], "-N")){
		}else{
			printf("\nArgument %d:'%s' is invalid! Use '-h' for options", i, argv[i]);
			return(1);
		}
	}
	
	if(file > 1){
		printf("\nCannot open more than one data file at a time!\n"
				"Use '-h' for options");
				return(1);
	}
	
	return(0);
}

void argumentDecision(char** argv, int argc, FILE* fp, int* fileNumber){
		
		int i;
		double value;
		char* newName;
		
		for(i = 1; i < argc; i++){
			if(!strcmp(argv[i],"-n")){
				i++;
			}else if(!strcmp(argv[i],"-s")){
				i++;
				value = atof(argv[i]);
				printf("\nBegin Scale...");
				scale(fp, value, fileNumber);
			}else if(!strcmp(argv[i],"-o")){
				i++;
				value = atof(argv[i]);
				printf("\nBegin Offset...");
				offset(fp, value, fileNumber);
			}else if(!strcmp(argv[i],"-r")){
				i++;
				newName = argv[i];
				printf("\nBegin Rename...");
				renameFile(fp, newName);
			}else if(!strcmp(argv[i],"-h")){
				printf("\nBegin Help...");
				help();
			}else if(!strcmp(argv[i],"-S")){
				printf("\nBegin Statistics...");
				statistics(fp, fileNumber);
			}else if(!strcmp(argv[i],"-C")){
				printf("\nBegin CenterData...");
				centerData(fp, fileNumber);
			}else if(!strcmp(argv[i],"-N")){
				printf("\nBegin Normalize...");
				normalize(fp, fileNumber);
			}
		}
		
		return;
}

void scale(FILE* fp, double value, int* fileNumber){
	
	FILE* newFP;
	int numberOfData;
	int largestData;
	int* dataArray;
	char newFileName[20];
	int i;
	rewind(fp);
	sprintf(newFileName, "Scaled_Data_%.2d.txt", *fileNumber);
	printf("\nOpening %s...", newFileName);
	
	newFP = fopen(newFileName, "w");
	if(newFP == NULL){
		printf("\nUnable create file %s. Scaling terminated!", newFileName);
		return;
	}
	
	fscanf(fp, "%d %d\n", &numberOfData, &largestData);
	
	dataArray = malloc(numberOfData* sizeof(int));
	
	for(i = 0; i < numberOfData; i++){
		fscanf(fp, "%d", dataArray +i);
	}
	
	
	fprintf(newFP, "%d %d\t\t%d %.4f", numberOfData, largestData, numberOfData, (value)*(double)(largestData));
	
	for(i = 0; i < numberOfData; i++){
		fprintf(newFP, "\n%d\t\t%.4f", dataArray[i],(double)(dataArray[i])*value);
	}
	
	printf("\nClosing %s...", newFileName);
	if(fclose(newFP) != 0){
		printf("\nFile was not close successfully!");
	}
	free(dataArray);
	
	return;
}

void offset (FILE* fp, double value, int* fileNumber){
	FILE* newFP;
	int numberOfData;
	int largestData;
	int* dataArray;
	char newFileName[20];
	int i;
	
	rewind(fp);
	sprintf(newFileName, "Offset_Data_%.2d.txt", *fileNumber);
	printf("\nOpening %s...", newFileName);
	
	newFP = fopen(newFileName, "w");
	if(newFP == NULL){
		printf("\nUnable create file %s. Scaling terminated!", newFileName);
		return;
	}
	
	fscanf(fp, "%d %d\n", &numberOfData, &largestData);
	
	dataArray = malloc(numberOfData* sizeof(int));
	
	for(i = 0; i < numberOfData; i++){
		fscanf(fp, "%d", dataArray +i);
	}
	
	
	fprintf(newFP, "%d %d\t\t%d %.4f", numberOfData, largestData, numberOfData, (double)(largestData) + value);
	
	for(i = 0; i < numberOfData; i++){
		fprintf(newFP, "\n%d\t\t%.4f", dataArray[i],((double)(dataArray[i]) + value));
	}
	
	printf("\nClosing %s...", newFileName);
	if(fclose(newFP) != 0){
		printf("\nFile was not close successfully!");
	}
	free(dataArray);
	
}
void renameFile (FILE* fp, char* newName){
	
	FILE* newFP;
	int i;
	int numberOfData;
	int buffer;
	
	rewind(fp);
	printf("\nOpening new file %s...", newName);

	newFP = fopen(newName, "w");
	
	if(newFP == NULL){
		printf("\nUnable to create file %s. Rename terminated!", newName);
	}
	
	fscanf(fp, "%d %d", &numberOfData, &i);
	fprintf(newFP, "%d %d", numberOfData, i);
	
	for(i = 0; i < numberOfData; i++){
		fscanf(fp, "%d", &buffer);
		fprintf(newFP, "\n%d", buffer);
	}
	
	printf("\nClosing new file %s...", newName);
	if(fclose(newFP) != 0){
		printf("\nFile was not close successfully!");
	}
	
}
void help(){
	
	printf("\n****************HELP MESSAGE****************");
	printf("\nThis program accepts command line arguments in the form:"
			"\n\n./a [argument][SPACE][value][SPACE][argument]..."
			"\n\nList of arguments:"
			"\n\n-n [value] : Used to specify which Raw Data File to use for data manipulation."
			"\n\t\t[value] is the number corresponding to the Raw Data File number."
			"\n\t\tNOTE: Only one file can be manipulated at a time."
			"\n\n-s [value] : Used to scale the data located in the specified file by [value]."
			"\n\t\tScaled data will be written to the file named Scaled_Data_[file number].txt"
			"\n\n-o : Used to offset the data located int he specified file by [value]."
			"\n\t\tOffset data will be written to the file named Offset_Data_[file number].txt"
			"\n\n-r [new file name] : Used to create a copy of the specified file with the"
			"\n\t\tgiven name."
			"\n\n-S : Used to get the statistic of the specified file. Statistics will be written"
			"\n\t\tto the file named Statistics_Data_[file number].txt"
			"\n\n-C : Used to center the data. The centered data will be written to the file"
			"\n\t\tnamed Centered_Data_[file number].txt"
			"\n\n-N : Used to normalize the data. The normalized data will be written to the file"
			"\n\t\tnamed Normalized_Data_[file number].txt");
	
}
void statistics (FILE* fp, int* fileNumber){
	
	FILE* newFP;
	int i;
	int buffer;
	int numberOfData;
	int largestNumber;
	int biggestNumber = 0;
	char newFileName[25];
	double mean = 0.0;
	
	rewind(fp);
	
	sprintf(newFileName, "Statistics_Data_%.2d.txt", *fileNumber);
	printf("\nOpening %s...", newFileName);
	
	newFP = fopen(newFileName, "w");
	if(newFP == NULL){
		printf("\nUnable create file %s. Statistics terminated!", newFileName);
		return;
	}
	
	fscanf(fp, "%d %d", &numberOfData, &largestNumber);
	
	for(i = 0; i < numberOfData; i++){
		fscanf(fp, "%d", &buffer);
		if(buffer > biggestNumber){
			biggestNumber = buffer;
		}
		mean += buffer;
	}
	
	mean = mean / (double)(numberOfData);
	
	fprintf(newFP, "%.4f %d", mean, biggestNumber);
	
	
	printf("\nClosing %s...", newFileName);
	if(fclose(newFP) != 0){
		printf("\nFile was not close successfully!");
	}
	
	
}
void centerData (FILE* fp, int* fileNumber){
	
	FILE* newFP;
	int i;
	int* dataArray;
	int numberOfData;
	int largestNumber;
	char newFileName[25];
	double mean = 0.0;
	
	rewind(fp);
	
	sprintf(newFileName, "Centered_Data_%.2d.txt", *fileNumber);
	printf("\nOpening %s...", newFileName);
	
	newFP = fopen(newFileName, "w");
	if(newFP == NULL){
		printf("\nUnable create file %s. Statistics terminated!", newFileName);
		return;
	}
	
	fscanf(fp, "%d %d", &numberOfData, &largestNumber);
	dataArray = malloc(numberOfData * sizeof(int));
	
	for(i = 0; i < numberOfData; i++){
		fscanf(fp, "%d", &dataArray[i]);
		mean += dataArray[i];
		
	}
	mean = mean / (double)(numberOfData);
	fprintf(newFP, "%d %d\t\t%d %.4f", numberOfData, largestNumber, numberOfData, (double)(largestNumber)-mean);
	for(i = 0; i < numberOfData; i++){
		fprintf(newFP, "\n%d\t\t%.4f", dataArray[i], (double)(dataArray[i]) - mean); 
	}
	
	
	printf("\nClosing %s...", newFileName);
	if(fclose(newFP) != 0){
		printf("\nFile was not close successfully!");
	}
	free(dataArray);
}
void normalize (FILE* fp, int* fileNumber){
	FILE* newFP;
	int i;
	int* dataArray;
	int numberOfData;
	int largestNumber;
	char newFileName[25];
	
	rewind(fp);
	
	sprintf(newFileName, "Normalized_Data_%.2d.txt", *fileNumber);
	printf("\nOpening %s...", newFileName);
	
	newFP = fopen(newFileName, "w");
	if(newFP == NULL){
		printf("\nUnable create file %s. Statistics terminated!", newFileName);
		return;
	}
	
	fscanf(fp, "%d %d", &numberOfData, &largestNumber);
	dataArray = malloc(numberOfData * sizeof(int));
	
	for(i = 0; i < numberOfData; i++){
		fscanf(fp, "%d", &dataArray[i]);
		
	}
	
	fprintf(newFP, "%d %d\t\t%d %.4f", numberOfData, largestNumber, numberOfData, (double)(largestNumber) / (double)(largestNumber));
	for(i = 0; i < numberOfData; i++){
		fprintf(newFP, "\n%d\t\t%.4f", dataArray[i], (double)(dataArray[i]) / (double)(largestNumber)); 
	}
	
	
	printf("\nClosing %s...", newFileName);
	if(fclose(newFP) != 0){
		printf("\nFile was not close successfully!");
	}
	free(dataArray);
	
}
