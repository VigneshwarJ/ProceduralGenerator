#pragma once
#include "Mesh.h"
class Entity
{
private:
	Mesh* textured_Mesh;
	glm::vec3 Position;
	glm::vec3 Rotation;
	float Scale;
public:
	Entity(Mesh* mesh,glm::vec3 Position = glm::vec3(0.0f,0.0f,0.0f), 
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),float scale=1.0f);
	void changePosition(glm::vec3 position);
	void changeRotation(glm::vec3 rotation);
	Mesh* returnMesh() const;
	glm::vec3 returnPosition() const;
	glm::vec3 returnRotation() const;
	float returnScale() const;

};

