#include "Mesh.h"
#include <iostream>
Mesh::Mesh(Vertex* vertices,unsigned int* indeces, unsigned int numVertices,unsigned int numIndeces)
{
	m_draw_count = numIndeces;
	glGenVertexArrays(1, &m_VertexArrayObject); 
	glBindVertexArray(m_VertexArrayObject);
	/*
	Vertex array buffer object
	*/
	glGenBuffers(NUM_BUFF, m_VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER ,m_VertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]),vertices,GL_STATIC_DRAW);
	glGenBuffers(NUM_BUFF, m_VertexArrayBuffers);
	/*
	index array buffer object
	*/
	glGenBuffers(NUM_BUFF, &m_IndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndeces * sizeof(indeces[0]), indeces, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}
void Mesh::draw()
{
	glBindVertexArray(m_VertexArrayObject);

	glDrawElements(GL_TRIANGLES,m_draw_count, GL_UNSIGNED_INT,nullptr);

	glBindVertexArray(0);
}
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
}