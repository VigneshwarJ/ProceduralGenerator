#include "Mesh.h"
#include <iostream>
Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_draw_count = numVertices;
	glGenVertexArrays(1, &m_VertexArrayObject); 
	glBindVertexArray(m_VertexArrayObject);
	glGenBuffers(NUM_BUFF, m_VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER ,m_VertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]),vertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}
void Mesh::draw()
{
	glBindVertexArray(m_VertexArrayObject);

	glDrawArrays(GL_TRIANGLES,0,m_draw_count);

	glBindVertexArray(0);
}
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
}