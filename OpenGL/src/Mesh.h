#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
class Mesh
{
public:
	Mesh(Vertex* vertices,unsigned int* indeces, unsigned int numVertices, unsigned int numIndeces);

	unsigned int getDrawCount() const;
	virtual ~Mesh() ;
	void bindAll() const;
private:
	VertexArray* m_VAO;
	IndexBuffer* m_IBO;
	VertexBuffer* m_VBO;
	unsigned int m_draw_count;
};

