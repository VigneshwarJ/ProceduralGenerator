#pragma once
#include <string>
#include <glm.hpp>
#include <vector>
#include <unordered_map>
#include "gtc/matrix_transform.hpp"
#include "../Scenegraph/SceneItem.h"

//using old symbols
//F draw a line
//+ left - right
//[ push and ] pop

class Ltrees
{
public:
	Ltrees(int loop);
	SceneItemSharedPtr returnMesh();
private:
	void applyRules(std::string& rules);
	void generate(char r);
	void drawtubes(glm::mat2x2 transform, glm::vec3 position);
	std::vector<uint32_t> indeces;
	std::vector<Vertex> vertices;

	glm::vec3 pos;
	std::vector<glm::vec3> locations;
	std::vector<glm::mat4x4> location;
	std::vector<unsigned int> thetas;
	std::vector<float> sizes;
	std::string rule;
	std::unordered_map<char, std::string> maps;
	glm::mat4 rotate;
	float theta;
	void createmesh();
	int index;
	int LOOP;
	float size = 1.0f;
	int count;
	float thetacount;
	void create();
	glm::mat4x4 scale;
	std::uint32_t n = 4;

};

