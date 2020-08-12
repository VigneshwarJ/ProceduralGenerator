#pragma once
#include <glm.hpp>
class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	glm::vec3 getPosition();
	glm::vec3 getColor();
private:
	glm::vec3 position;
	glm::vec3 color;
};

