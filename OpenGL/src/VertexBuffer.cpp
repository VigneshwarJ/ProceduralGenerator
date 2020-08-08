#include "VertexBuffer.h"
#include <iostream>


VertexBuffer::VertexBuffer(unsigned int numVertices,float* vertices,unsigned int number) {
	glGenBuffers(1, &m_VertexBufferObject);
	std::cout <<"err" << glGetError() << std::endl; // returns 0 (no error)
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
	std::cout << "err" << glGetError() << std::endl; // returns 0 (no error)
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GL_FLOAT) * number, vertices, GL_STATIC_DRAW);
	std::cout << "err" << glGetError() << std::endl; // returns 0 (no error)
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