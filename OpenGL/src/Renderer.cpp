#include "Renderer.h"
#include "gtc/matrix_transform.hpp"
#include <iostream>
Renderer::Renderer(Camera* camera) {
	m_shader = new Shader("res/basic");
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
	m_camera = camera;
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
	/*
	glm::vec3(100.5,100.5,15),
		glm::vec3(100.5,200.5,15),
		glm::vec3( 200.5,100.5,15),
		glm::vec3(200.5,200.5,15)
	*/
	glm::mat4 View = m_camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(70.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	glm::mat4 Model1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 Model = glm::scale(Model1, glm::vec3(0.8f, 0.8f, 0.8f));
	glm::mat4 MVP = projection *View;

	m_shader->setUniformLocationMat4("MVP", MVP);
	glDrawElements(GL_TRIANGLES, mesh->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, mesh.getDrawCount());
}
