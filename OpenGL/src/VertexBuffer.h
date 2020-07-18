#pragma once
#include "Vertex.h"
class VertexBuffer
{
public:
	VertexBuffer(unsigned int numVertices, Vertex* vertices);
	void BindBuffer() const;
	void UnBindBuffer() const;
	~VertexBuffer();
private:
	GLuint m_VertexBufferObject;

};

