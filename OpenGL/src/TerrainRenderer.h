#pragma once
#include "Shader.h"
#include <glm.hpp>
#include "Entity.h"
#include "gtc/matrix_transform.hpp"
#include "Terrain.h"
class TerrainRenderer
{
public:
	TerrainRenderer(Shader* shader, glm::mat4 projectionMatrix);
	void render( std::list<Terrain*> entities);
	void prepareInstance(Terrain* entity);
private:
	Shader* m_shader;
};

