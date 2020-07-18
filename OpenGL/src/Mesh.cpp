#include "Mesh.h"
#include <iostream>
Mesh::Mesh(Vertex* vertices,unsigned int* indeces, unsigned int numVertices,unsigned int numIndeces)
{
	m_draw_count = numIndeces;
	m_VAO = new VertexArray();
	/*
	Vertex array buffer object 
	*/
	m_VBO = new VertexBuffer(numVertices, vertices);
	/*
	index array buffer object
	*/
	m_IBO = new IndexBuffer(numIndeces, indeces);
	
}
unsigned int Mesh::getDrawCount() const{
	return m_draw_count;
}
void Mesh::bindAll() const
{
	m_VAO->AddBuffer(0, *m_VBO, 3);
	m_VAO->bind();
	m_VBO->BindBuffer();
	m_IBO->BindBuffer();
}

Mesh::~Mesh()
{
	
}