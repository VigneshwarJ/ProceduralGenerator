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
void VertexArray::AddBuffer(unsigned int AttributeNo,const VertexBuffer& vbo,const int& elementCount)
{
	//std::cout << "hello" << std::endl;
	this->bind();
	vbo.BindBuffer();
	glEnableVertexAttribArray(AttributeNo);
	glVertexAttribPointer(AttributeNo, elementCount, GL_FLOAT, GL_FALSE, 0, 0);
	/*this->unbind();
	vbo.UnBindBuffer();*/
}
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_VertexArrayObject);
}