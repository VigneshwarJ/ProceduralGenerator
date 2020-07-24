#pragma once
#include <vector>
#include "VertexBuffer.h"
class VertexArray
{
public:
	VertexArray();
	void bind() const;
	void unbind() const;
	void AddBuffer(unsigned int AttributeNo, const VertexBuffer& vbo, const int& number);
	~VertexArray();
private:
	GLuint m_VertexArrayObject;
};

