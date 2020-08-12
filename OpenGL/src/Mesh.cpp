#include "Mesh.h"
#include <iostream>
Mesh::Mesh(float* vertices, unsigned int* indeces, float* text_coord, float* normals, unsigned int numVertices, unsigned int numIndeces, unsigned int num_text, unsigned int num_normals, Texture* texture)
{
	m_draw_count = numIndeces;
	//m_draw_count = numVertices;
	m_VAO = new VertexArray();
	/*
	Vertex array buffer object
	*/
	m_VBO = new VertexBuffer(numVertices, vertices, 3);
	m_TBO = new VertexBuffer(num_text, text_coord, 2);
	m_NBO = new VertexBuffer(num_normals, normals, 3);
	/*
	index array buffer object
	*/
	m_IBO = new IndexBuffer(indeces, numIndeces);
	if (texture != nullptr)
	{
		m_texture = texture;
	}

}
unsigned int Mesh::getDrawCount() const {
	return m_draw_count;
}
void Mesh::bindAll() const
{
	m_VAO->AddBuffer(0, *m_VBO, 3);
	m_VAO->AddBuffer(1, *m_TBO, 2);
	m_VAO->AddBuffer(2, *m_NBO, 3);

	m_VAO->bind();
	m_VBO->BindBuffer();
	m_TBO->BindBuffer();
	m_NBO->BindBuffer();
	m_IBO->BindBuffer();
	m_texture->bind();
}

Mesh::~Mesh()
{

}