#ifndef PG_RENDERABLEHANDLEROPENGL_H
#define PG_RENDERABLEHANDLEROPENGL_H


#include "../../Scenegraph/Vertex.h"
#include "../IRenderableHandler.h"
#include "BufferObjectOpenGL.h"




MAKE_SHARED(RenderableHandlerOpenGL);
class RenderableHandlerOpenGL
	: public IRenderableHandler
{
public:
	RenderableHandlerOpenGL();
	~RenderableHandlerOpenGL() override;

	void initialize(const Vertex* p_vertices,
		const uint32_t* p_indices,
		std::size_t number_of_vertices,
		std::size_t number_of_indices,
		GLenum primitive_type);
	void bind();
	void render();
	void unbind();

private:
	uint32_t mIndexCount;
	GLenum mPrimitiveType;
	BufferObjectOpenGL mIndexBuffer;
	GLuint mVertexArray;
	BufferObjectOpenGL mVertexBuffer;

};


#endif // PG_RENDERABLEHANDLEROPENGL_H
