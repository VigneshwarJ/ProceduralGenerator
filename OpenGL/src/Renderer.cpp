#include "Renderer.h"
#include "gtc/matrix_transform.hpp"
#include <iostream>
Renderer::Renderer(Camera* camera,Light* light) {
	m_shader = new Shader("res/basic");
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
	m_camera = camera;
	m_light = light;
}
void Renderer::prepare() {
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
}
void Renderer::render(const Entity& entity)
{
	Mesh* mesh = entity.returnMesh();
	mesh->bindAll();
	m_shader->bind();
	m_shader->setUniformLocation1i("textureSampler", 0);
	m_shader->setUniformLocation3f("LightColor", m_light->getColor());
	m_shader->setUniformLocation3f("lightPosition", m_light->getPosition());
	glm::mat4 View = m_camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(70.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	m_shader->setUniformLocationMat4("ProjectionMat", projection);
	m_shader->setUniformLocationMat4("ViewMat", View);
	
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), entity.returnPosition());
	glm::vec3 rotation = entity.returnRotation();
	Model = glm::rotate(Model, rotation.x, glm::vec3(1, 0, 0));
	Model = glm::rotate(Model, rotation.y, glm::vec3(0, 1, 0));
	Model = glm::rotate(Model, rotation.z, glm::vec3(0, 0, 1));
	float scale = entity.returnScale();
	Model = glm::scale(Model, glm::vec3(scale));
	m_shader->setUniformLocationMat4("TransformationMat", Model);
	glDrawElements(GL_TRIANGLES, mesh->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, mesh.getDrawCount());
}
