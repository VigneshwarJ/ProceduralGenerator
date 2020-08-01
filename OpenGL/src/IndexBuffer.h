#pragma once
#include "Vertex.h"
class IndexBuffer
{
public:
	IndexBuffer(unsigned int numIndeces, unsigned int* indeces);
	void BindBuffer();
	void UnBindBuffer();
	~IndexBuffer();
private:
	GLuint m_IndexBufferObject;
};

