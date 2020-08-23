#pragma once
#include <string>
#include <glm.hpp>
#include <vector>
#include <unordered_map>
#include "Mesh.h"
#include "gtc/matrix_transform.hpp"
#include "Loader.h"
#include "Entity.h"
//using old symbols
//F draw a line
//+ left - right
//[ push and ] pop

class Ltrees
{
public:
	Ltrees();
	Mesh* returnMesh();
	std::vector<Entity*> returnEntity() ;
private:
	void applyRules(std::string& rules);
	void generate(char r);
	void drawtubes(glm::mat2x2 transform, glm::vec3 position);
	std::vector<unsigned int> indeces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> tex;
	std::vector<glm::vec3> normals;
	glm::vec3 pos;
	std::vector<glm::vec3> locations;
	std::vector<float> thetas;
	std::string rule;
	std::unordered_map<char, std::string> maps;
	std::vector<Entity*> entities;
	glm::mat4 rotate;
	float theta;
	void createmesh();
	int index;
	int LOOP;
	int count;
	float thetacount;
	void create();
	
	Mesh* m;
};

