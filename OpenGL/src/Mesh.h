#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
class Mesh
{
public:
	Mesh(float* vertices,unsigned int* indeces, float* text_coord, float* normals, 
		unsigned int numVertices, unsigned int numIndeces, unsigned int num_text, 
		unsigned int num_normals, Texture* texture);
	unsigned int getDrawCount() const;
	virtual ~Mesh() ;
	void bindAll() const;
private:
	VertexArray* m_VAO;
	IndexBuffer* m_IBO;
	VertexBuffer* m_VBO;
	VertexBuffer* m_TBO;
	VertexBuffer* m_NBO;
	Texture* m_texture;
	unsigned int m_draw_count;
};

