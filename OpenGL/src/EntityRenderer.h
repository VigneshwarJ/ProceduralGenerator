#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Entity.h"
#include "gtc/matrix_transform.hpp"
class EntityRenderer
{
public:
	EntityRenderer(Shader* shader, glm::mat4 projectionMatrix);
	void render(std::unordered_map<Mesh*, std::list<Entity*>> entities);
	void prepareInstance(Entity* entity);
private:
	Shader* m_shader;

};

