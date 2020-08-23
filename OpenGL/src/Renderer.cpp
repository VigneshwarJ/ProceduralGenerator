#include "Renderer.h"

#include <iostream>
Renderer::Renderer() {
	m_shader = new Shader("res/basic");
	t_shader = new Shader("res/Terrain");
	glm::mat4 projection = glm::perspective(70.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	renderer = new EntityRenderer(m_shader, projection);
	Trenderer = new TerrainRenderer(t_shader, projection);
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
	std::cout << RAND_MAX;
}
void Renderer::prepare() {
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
}
void Renderer::render(Light* light, Camera* camera)
{
	m_shader->bind();
	m_shader->setUniformLocation1i("textureSampler", 0);
	m_shader->setUniformLocation3f("LightColor", light->getColor());
	m_shader->setUniformLocation3f("lightPosition", light->getPosition());
	glm::mat4 View = camera->GetViewMatrix();
	m_shader->setUniformLocationMat4("ViewMat", View);
	renderer->render(entities);
	m_shader->unbind();
	t_shader->bind();
	t_shader->setUniformLocation1i("textureSampler", 0);
	t_shader->setUniformLocation3f("LightColor", light->getColor());
	t_shader->setUniformLocation3f("lightPosition", light->getPosition());
	t_shader->setUniformLocationMat4("ViewMat", View);
	Trenderer->render(terrains);
	t_shader->unbind();

	
}

void Renderer::renderScene(std::vector<Entity*>const& entities, Light* lights, std::vector<Terrain*>const& terrains, Camera* camera)
{
	for (auto& entity : entities)
	{
		processEntities(entity);
	}
	for (auto terrain : terrains)
	{
		processTerrains(terrain);
	}
	//Light* light = lights[0];
	this->render(lights, camera);
}

void Renderer::processEntities( Entity* entity)
{
		Mesh* entityModel = entity->returnMesh();
		if (entities.find(entityModel) == entities.end())
		{
			std::list<Entity*> entitiylist;
			entitiylist.push_back(entity);
			entities.insert({ entityModel, entitiylist });
		}
		else
		{
			entities[entityModel].push_back(entity);
		}
}

void Renderer::processTerrains(Terrain* entity)
{
	terrains.push_back(entity);
}

