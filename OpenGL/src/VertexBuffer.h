#pragma once
#include "Vertex.h"
class VertexBuffer
{
public:
	VertexBuffer(unsigned int numVertices, float* vertices, unsigned int number);
	void BindBuffer() const;
	void UnBindBuffer() const;
	~VertexBuffer();
private:
	GLuint m_VertexBufferObject;

};

