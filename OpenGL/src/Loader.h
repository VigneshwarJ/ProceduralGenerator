#pragma once
#include "Mesh.h"
#include <fstream>
class Loader{
public:
	static Mesh* loadObject(const std::string& fileName);
private:
	Loader();
	~Loader();
};
