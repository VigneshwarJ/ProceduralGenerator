#include "BufferObjectOpenGL.h"


BufferObjectOpenGL::BufferObjectOpenGL()
	: m_VertexBufferObject(0), type(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, &m_VertexBufferObject);
}

BufferObjectOpenGL::~BufferObjectOpenGL()
{
	glDeleteBuffers(1, &m_VertexBufferObject);
}

void BufferObjectOpenGL::setType(GLenum buffer)
{
	type = buffer;
}

void BufferObjectOpenGL::setBufferData(const void* p_data,
	size_t data_size)
{
	glBindBuffer(type, m_VertexBufferObject);

	glBufferData(type,
		data_size, p_data, GL_STATIC_DRAW);
	//glBindBuffer(type, 0);
}

void BufferObjectOpenGL::bind()
{
	glBindBuffer(type, m_VertexBufferObject);
}

void BufferObjectOpenGL::unbind()
{
	glBindBuffer(type, 0);
}
