#pragma once
#include<GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Entity.h"
#include "Light.h"
#include "EntityRenderer.h"
#include "Terrain.h"
#include "TerrainRenderer.h"
class Renderer
{
public:
	Renderer();
	void prepare();
	void render(Light* light, Camera* camera);
	void processEntities( Entity* entity);
	void processTerrains(Terrain* entity);
private:
	Shader* m_shader;
	Shader* t_shader;
	Camera* m_camera;
	Light* m_light;
	EntityRenderer* renderer;
	TerrainRenderer* Trenderer;
	std::unordered_map<Mesh*, std::list<Entity*>> entities;
	std::list<Terrain*> terrains;
};

