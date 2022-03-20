#ifndef PG_BufferObjectOPENGL_H
#define PG_BufferObjectOPENGL_H



#include "../IBufferObject.h"

MAKE_SHARED(BufferObjectOpenGL);

class BufferObjectOpenGL
	: public IBufferObject
{
public:
	BufferObjectOpenGL();
	~BufferObjectOpenGL() override;
	void setType(GLenum buffer);
	void setBufferData(const void* p_data,
		size_t data_size);
	void bind();
	void unbind();

private:
	GLuint m_VertexBufferObject;
	GLenum type;
};



#endif // PG_BufferObjectOPENGL_H
