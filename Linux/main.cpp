#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>   //For file writing
#include <unistd.h>  //For sleep function
#include <ctime>     //For system time

std::string getOutPutFromCommand(std::string command);
std::string findDataFromString(std::string stringToSearch, std::string dataField, int offset);


int main() {

	//Offset for data reading point
	int dataOffset = 57; 

	//Filestream
	std::ofstream outputFile;

	//Data values
	std::string RXBytesVal;

	//Holds the output of entire command
	std::string output; 
	

	int counter = 0;

	while (1) { //Infinite loop so we can keep on picking up data
		
		//Get output from the command and store it
		output = getOutPutFromCommand("ip -s -d link show"); 
		
		//Get system time right after command call
		time_t t = time(0);
		struct tm * now = localtime( & t );

		//Find datafields and store data
		RXBytesVal = findDataFromString(output, "RX: bytes", dataOffset);

		std::cout << RXBytesVal << std::endl; //Temp print

		std::cout << "\n" << std::endl;

		//We have to open and close the file every time we want to write to it. I dont know why ¯\_(ツ)_/¯
		outputFile.open("outputFile.txt", std::ofstream::out | std::ofstream::app);
		outputFile << (now->tm_mon + 1) << "-" << now->tm_mday  << "-"  << (now->tm_year + 1900); //Date printing
		outputFile << ", " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " | "; //Time printing		

		outputFile << "RX: " << RXBytesVal << " \n";
		outputFile.close();

		usleep(0.25/*seconds*/ * 1000000); //TODO: Probably remove this? So far just a delay to test the system.		

		counter++;
	}

	return 0;
}

//Runs the actual command, returns the whole output
std::string getOutPutFromCommand(std::string command) { 

	std::string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	command.append(" 2>&1");

	stream = popen(command.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		pclose(stream);
	}
	return data;
}

//Finds the specific data from the output based on an offset and returns the value in string format
std::string findDataFromString(std::string stringToSearch, std::string dataField, int offset) {
	std::string data;
	std::size_t dataPos = stringToSearch.find(dataField);

	if (dataPos != std::string::npos) {

		int i = 0;

		while(stringToSearch[dataPos + offset + i] != ' ') {
			data += stringToSearch[dataPos + offset + i];
			i++;
		}	
	}

	return data;
}
