#include "EntityRenderer.h"
#include <iostream>

EntityRenderer::EntityRenderer(Shader* shader, glm::mat4 projectionMatrix)
{
	m_shader = shader;
	m_shader->bind();
	m_shader->setUniformLocationMat4("ProjectionMat", projectionMatrix);
	
}

void EntityRenderer::render(std::unordered_map<Mesh*, std::list<Entity*>> entities)
{
	for (auto& entityMap : entities) {
		 Mesh* mesh = entityMap.first;
		 //std::cout << mesh << std::endl;
		mesh->bindAll();
		Texture* tex = mesh->returnTexture();

		m_shader->setUniformLocation1f("reflectivity", 0.0);
		m_shader->setUniformLocation1f("shineDamper", tex->returnShineDampner());

		std::list<Entity*> batch = entityMap.second;
		for (Entity* entity : batch) {
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, mesh->getDrawCount(), GL_UNSIGNED_INT, 0);
		}
		mesh->unbindAll();
	}
}

void EntityRenderer::prepareInstance(Entity* entity)
{
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), entity->returnPosition());
	glm::vec3 rotation = entity->returnRotation();
	Model = glm::rotate(Model, rotation.x, glm::vec3(1, 0, 0));
	Model = glm::rotate(Model, rotation.y, glm::vec3(0, 1, 0));
	Model = glm::rotate(Model, rotation.z, glm::vec3(0, 0, 1));
	float scale = entity->returnScale();
	Model = glm::scale(Model, glm::vec3(scale));
	m_shader->setUniformLocationMat4("TransformationMat", Model);
}
