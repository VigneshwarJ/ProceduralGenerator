#include "Entity.h"

Entity::Entity(Mesh* mesh, glm::vec3 position,glm::vec3 rotation, float scale):
	textured_Mesh(mesh),Position(position),Rotation(rotation),Scale(scale)
{
}
void Entity::changePosition(glm::vec3 position)
{
	Position += position;
}
void Entity::changeRotation(glm::vec3 rotation)
{
	Rotation += rotation;
}

 Mesh* Entity::returnMesh() const
{
	return textured_Mesh;
}
