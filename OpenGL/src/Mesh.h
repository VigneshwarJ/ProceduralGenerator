#pragma once
#include<glm.hpp>
#include<GL/glew.h>
class Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->position = pos;
	}
private:
	glm::vec3 position;
};
class Mesh
{
public:
	Mesh(Vertex* vertices,unsigned int numVertices);
	virtual ~Mesh();
	void draw();
private:
	enum 
	{
		POSITION_VB,

		NUM_BUFF
	};
	GLuint m_VertexArrayObject;
	GLuint m_VertexArrayBuffers[NUM_BUFF];
	unsigned int m_draw_count;
};

