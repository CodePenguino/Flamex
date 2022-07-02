#include "util.hpp"
#include <iostream>
#include <fstream>

std::string readFile(const char* fileName)
{
	std::ifstream file;
	file.open(fileName);

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + '\n');
		}
	}
	else
	{
		std::cerr << "Error: Unable to load shader: " << fileName << '\n';
	}

	return output;
}
