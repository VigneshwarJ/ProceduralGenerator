#pragma once
#include <vector>
#include "VertexBuffer.h"
class VertexArray
{
public:
	VertexArray();
	void bind() const;
	void unbind() const;
	void bindAttributes(const unsigned int& AttributeNo, const VertexBuffer& vbos, const int& elementCount);
	void enableAttributes(const unsigned int& AttributeNo);
	void disableAttributes(const unsigned int& AttributeNo);
	~VertexArray();
private:
	GLuint m_VertexArrayObject;
};

