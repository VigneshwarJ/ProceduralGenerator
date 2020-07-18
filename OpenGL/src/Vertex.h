#pragma once
#include<GL/glew.h>
#include<glm.hpp>
class Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->position = pos;
	}
private:
	glm::vec3 position;
};