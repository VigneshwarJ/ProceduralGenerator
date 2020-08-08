#pragma once
#include "Vertex.h"
class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indeces, unsigned int numIndeces);
	void BindBuffer();
	void UnBindBuffer();
	~IndexBuffer();
private:
	GLuint m_IndexBufferObject;
};

