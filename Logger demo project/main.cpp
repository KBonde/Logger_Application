#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

std::string getOutPutFromCommand(std::string command);
std::string findDataFromString(std::string stringToSearch, std::string dataField, uint8_t length, uint8_t offset);


int main() {

	int ipOffset = 36;
	int ipLength = 12;

	std::ofstream dataFile;

	std::string output = getOutPutFromCommand("ip -s -d link show");

	std::string ip;

	dataFile.open("dataFile.txt", std::ofstream::out | std::ofstream::app);

	int counter = 0;

	while (1) {
		counter++;
		std::size_t ipPos = output.find("IPv4 Address. . . . . . . . . . . :");

		if (ipPos != std::string::npos) {

			for (int i = 0; i < ipLength; i++) {
				ip += output[ipPos + ipOffset + i];
			}
		}

		ip = findDataFromString(output, "IPv4 Address. . . . . . . . . . . :", ipLength, ipOffset);


		system("PAUSE");
	}

	return 0;
}

std::string getOutPutFromCommand(std::string command) {

	std::string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	command.append(" 2>&1");

	stream = _popen(command.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		_pclose(stream);
	}
	return data;
}

std::string findDataFromString(std::string stringToSearch, std::string dataField, uint8_t length, uint8_t offset) {
	std::string data;
	std::size_t dataPos = stringToSearch.find(dataField);

	if (dataPos != std::string::npos) {

		for (int i = 0; i < length; i++) {
			data += stringToSearch[dataPos + offset + i];
		}
	}

	return data;
}
