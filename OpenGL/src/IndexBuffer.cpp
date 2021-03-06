#include "IndexBuffer.h"
#include <iostream>
IndexBuffer::IndexBuffer(unsigned int* indeces,unsigned int numIndeces) {
	glGenBuffers(1, &m_IndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndeces * sizeof(indeces[0]), indeces, GL_STATIC_DRAW);
}
void IndexBuffer::BindBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
}
void IndexBuffer::UnBindBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_IndexBufferObject);
}