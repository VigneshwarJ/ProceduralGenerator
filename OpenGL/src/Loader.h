#pragma once
#include "Mesh.h"
#include <fstream>
#include <iostream>
class Loader{
public:
	static Mesh* loadObject(const std::string& fileName, const std::string& textureName = nullptr);
private:
	Loader();
	~Loader();
};