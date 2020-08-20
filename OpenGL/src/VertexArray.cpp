#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);
}
void VertexArray::bind() const{
	glBindVertexArray(m_VertexArrayObject);
}
void VertexArray::unbind() const {
	glBindVertexArray(0);
}
void VertexArray::bindAttributes(const unsigned int& AttributeNo,const VertexBuffer& vbo,const int& elementCount)
{
	vbo.BindBuffer();
	glEnableVertexAttribArray(AttributeNo);
	glVertexAttribPointer(AttributeNo, elementCount, GL_FLOAT, GL_FALSE, 0, 0);
	vbo.UnBindBuffer();
}
void VertexArray::enableAttributes(const unsigned int& AttributeNo)
{
	glEnableVertexAttribArray(AttributeNo);
}
void VertexArray::disableAttributes(const unsigned int& AttributeNo)
{
	glDisableVertexAttribArray(AttributeNo);
}
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_VertexArrayObject);
}