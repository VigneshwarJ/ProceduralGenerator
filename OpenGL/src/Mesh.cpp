#include "Mesh.h"
#include <iostream>
Mesh::Mesh(float* vertices,unsigned int* indeces, unsigned int numVertices,unsigned int numIndeces,float* text_coord,unsigned int num_text)
{
	m_draw_count = numIndeces;
	m_VAO = new VertexArray();
	/*
	Vertex array buffer object 
	*/
	m_VBO = new VertexBuffer(numVertices, (float*)vertices,3);
	m_TBO = new VertexBuffer(num_text, (float*)text_coord,2);
	/*
	index array buffer object
	*/
	m_IBO = new IndexBuffer(numIndeces, indeces);
	m_texture = new Texture("res/grassTexture.png");
	
}
unsigned int Mesh::getDrawCount() const{
	return m_draw_count;
}
void Mesh::bindAll() const
{
	m_VAO->AddBuffer(0, *m_VBO, 3);
	m_VAO->AddBuffer(1, *m_TBO, 2);
	m_VAO->bind();
	m_VBO->BindBuffer();
	m_IBO->BindBuffer();
	m_texture->bind();
}

Mesh::~Mesh()
{
	
}