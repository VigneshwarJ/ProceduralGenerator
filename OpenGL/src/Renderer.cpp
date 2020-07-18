#include "Renderer.h"
Renderer::Renderer() {
	m_shader = new Shader("res/basic");
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
}
void Renderer::prepare() {
	glClearColor(0.12f, 0.21f, 0.15f, 1.0f);
}
void Renderer::render(const Mesh& mesh)
{
	mesh.bindAll();
	m_shader->bind();
	glDrawElements(GL_TRIANGLES, mesh.getDrawCount(), GL_UNSIGNED_INT, nullptr);
}
