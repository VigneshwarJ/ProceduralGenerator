#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(Shader* shader, glm::mat4 projectionMatrix)
{
	m_shader = shader;
	m_shader->bind();
	m_shader->setUniformLocationMat4("ProjectionMat", projectionMatrix);
	m_shader->setUniformLocation1i("textureSampler", 0);
	m_shader->setUniformLocation1i("RSampler", 1);
	m_shader->setUniformLocation1i("GSampler", 2);
	m_shader->setUniformLocation1i("BSampler", 3);

}

void TerrainRenderer::render(std::list<Terrain*> entities)
{
	for (auto& entity : entities) {
		Mesh* mesh = entity->getModel();
		mesh->bindAll();
		prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, mesh->getDrawCount(), GL_UNSIGNED_INT, 0);
		mesh->unbindAll();
	}
}

void TerrainRenderer::prepareInstance(Terrain* entity)
{
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), {entity->getX(),0.0f,entity->getZ()});
	m_shader->setUniformLocationMat4("TransformationMat", Model);
	entity->ground->bind(1);
	entity->grass->bind(2);
	entity->slope->bind(3);


}