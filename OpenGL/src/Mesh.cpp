#include "Mesh.h"
#include <iostream>
Mesh::Mesh(float* vertices, unsigned int* indeces, float* text_coord, 
	float* normals, unsigned int numVertices, unsigned int numIndeces, 
	unsigned int num_text, unsigned int num_normals, Texture* texture)
{
	m_draw_count = numIndeces;
	//m_draw_count = numVertices;
	m_VAO = new VertexArray();
	/*
	Vertex array buffer object
	*/
	int temp = vertices[0];
	//std::cout <<  "temp >"<<temp << std::endl;
	m_VBO = new VertexBuffer(numVertices, vertices, 3);
	m_TBO = new VertexBuffer(num_text, text_coord, 2);
	m_NBO = new VertexBuffer(num_normals, normals, 3);
	/*
	index array buffer object
	*/
	m_IBO = new IndexBuffer(indeces, numIndeces);
    m_texture = texture;
	this->bindAttributes();
}
unsigned int Mesh::getDrawCount() const {
	return m_draw_count;
}
void Mesh::bindAttributes() const
{
	m_VAO->bind();
	m_VAO->bindAttributes(0, *m_VBO, 3);
	m_VAO->bindAttributes(1, *m_TBO, 2);
	m_VAO->bindAttributes(2, *m_NBO, 3);
	m_VAO->unbind();
}

void Mesh::bindAll() const
{
	m_VAO->bind();
	m_VAO->enableAttributes(0);
	m_VAO->enableAttributes(1);
	m_VAO->enableAttributes(2);
	m_texture->bind();
}
void Mesh::unbindAll() const
{
	m_texture->unbind();
	m_VAO->disableAttributes(0);
	m_VAO->disableAttributes(1);
	m_VAO->disableAttributes(2);
	m_VAO->unbind();
}

Mesh::~Mesh()
{

}



Texture* Mesh::returnTexture() const
{
	return m_texture;
}
