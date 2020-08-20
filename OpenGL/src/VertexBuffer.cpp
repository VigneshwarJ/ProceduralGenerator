#include "VertexBuffer.h"
#include <iostream>


VertexBuffer::VertexBuffer(unsigned int numVertices,float* vertices,unsigned int number) {
	glGenBuffers(1, &m_VertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);

	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GL_FLOAT) * number, vertices, GL_STATIC_DRAW);

}
void VertexBuffer::BindBuffer() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
}
void VertexBuffer::UnBindBuffer() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_VertexBufferObject);
}