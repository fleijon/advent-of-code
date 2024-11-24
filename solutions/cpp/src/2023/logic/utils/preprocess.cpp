#include "preprocess.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

bool readFile(const std::string& filepath, std::vector<std::string>& outTarget) {

	std::ifstream readfile(filepath);

	if (!readfile.is_open())
		return false;

	for( std::string line; std::getline(readfile, line); )
	{
		outTarget.emplace_back(line);
	}

	return true;
}

inline void split(const std::string& line, char delimiter, std::vector<std::string>& outputTarget ) {
	std::stringstream stream(line);

	for( std::string subline; std::getline(stream, subline, delimiter); )
	{
		outputTarget.emplace_back(subline);
	}
}

bool LoadInput(const std::string& filepath, char delimiter, input_format& outputTarget) {

	std::vector<std::string> fileContent;

	if (bool readResult = readFile(filepath, fileContent); !readResult) {

		std::cout << "Failed to read the file: " << filepath << std::endl;

		return false;
	}

	for (const auto& line : fileContent)
	{
		std::vector<std::string> splittedLine;
		split(line, delimiter, splittedLine);
		outputTarget.emplace_back(splittedLine);
	}

	return true;
}