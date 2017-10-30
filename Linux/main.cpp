#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

std::string getOutPutFromCommand(std::string command);
std::string findDataFromString(std::string stringToSearch, std::string dataField, int length, int offset);


int main() {

	int ipOffset = 57 + 11; //offset for data reading point
	int ipLength = 5; //Lenght of the data

	std::ofstream dataFile;

	std::string output = getOutPutFromCommand("ip -s -d link show");

	std::string ip;

	dataFile.open("dataFile.txt", std::ofstream::out | std::ofstream::app);

	int counter = 0;

	char x;

	while (1) {

		x = NULL;

		counter++;
		std::size_t ipPos = output.find("RX: bytes");

		if (ipPos != std::string::npos) {

			for (int i = 0; i < ipLength; i++) {
				ip += output[ipPos + ipOffset + i];
			}
		}

		ip = findDataFromString(output, "RX: bytes", ipLength, ipOffset);

		std::cout << ip << std::endl;

		std::cout << "test" << std::endl;

		std::cin >> x;
	}

	return 0;
}

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

std::string findDataFromString(std::string stringToSearch, std::string dataField, int length, int offset) {
	std::string data;
	std::size_t dataPos = stringToSearch.find(dataField);

	if (dataPos != std::string::npos) {

		int i = 0;

		for (int i = 0; i < 1000; i++) {
			if(stringToSearch[dataPos + offset + i] != ' ') {
				data += stringToSearch[dataPos + offset + i];
			} else {
				break;			
			}
		}
		
	}

	return data;
}
