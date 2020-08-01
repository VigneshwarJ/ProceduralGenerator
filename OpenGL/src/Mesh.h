#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
class Mesh
{
public:
	Mesh(float* vertices,unsigned int* indeces, unsigned int numVertices, unsigned int numIndeces,float* text_coord, unsigned int num_text);
	unsigned int getDrawCount() const;
	virtual ~Mesh() ;
	void bindAll() const;
private:
	VertexArray* m_VAO;
	IndexBuffer* m_IBO;
	VertexBuffer* m_VBO;
	VertexBuffer* m_TBO;
	Texture* m_texture;
	unsigned int m_draw_count;
};

