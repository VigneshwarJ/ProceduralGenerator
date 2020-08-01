#include "Loader.h"
#include <iostream>

Loader::Loader()
{
}

Loader::~Loader()
{
}

Mesh* Loader::loadObject(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());
	if (file.is_open())
	{
		while (file.good())
		{   
		//	getline(file, line);
		//	output.append(line + "\n");
		//	/*std::cout << line << std::endl;*/
		}
	}
	else {
		std::cout << "load the file correctly" << errno;
	}
	return nullptr;
}
