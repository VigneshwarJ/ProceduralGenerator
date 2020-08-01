#pragma once
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 viewMat();
private:
	glm::mat4 View;
	glm::vec3 position;
	glm::vec3 angle;

};

