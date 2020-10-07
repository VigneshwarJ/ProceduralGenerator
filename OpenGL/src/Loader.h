#pragma once
#include "Mesh.h"
#include <fstream>
#include <iostream>
class Loader{
public:
	static Mesh* loadObject(const std::string& fileName, const std::string& textureName = nullptr);
	static void loadObject(const std::string& fileName, unsigned int*& indecesp, std::vector<glm::vec3>& vertices, float*& normals, float*& textures);
private:
	Loader();
	~Loader();
};