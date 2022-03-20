#include "RenderableHandlerOpenGL.h"




RenderableHandlerOpenGL::RenderableHandlerOpenGL() :
	mIndexCount(0),
	mPrimitiveType(GL_TRIANGLES),
	mIndexBuffer(),
	mVertexArray(0),
	mVertexBuffer()
{

}

RenderableHandlerOpenGL::~RenderableHandlerOpenGL()
{

}


void RenderableHandlerOpenGL::initialize(const Vertex* p_vertices,
	const uint32_t* p_indices,
	std::size_t number_of_vertices,
	std::size_t number_of_indices,
	GLenum primitive_type)
{
	mPrimitiveType = primitive_type;
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	mVertexBuffer.setType(GL_ARRAY_BUFFER);

	mVertexBuffer.bind();
	mVertexBuffer.setBufferData(
		static_cast<const void*>(&p_vertices[0]),
		(sizeof(Vertex) * number_of_vertices));




	mIndexBuffer.setType(GL_ELEMENT_ARRAY_BUFFER);
	mIndexBuffer.bind();
	mIndexCount = static_cast<uint32_t>(number_of_indices);
	mIndexBuffer.setBufferData(
		static_cast<const void*>(&p_indices[0]),
		(sizeof(p_indices[0]) * number_of_indices));


	glEnableVertexAttribArray(0);
	// Vertex positions
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(const void*)offsetof(Vertex, mPosition));

	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(const void*)offsetof(Vertex, mTextureCoordinate));

	// Normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(const void*)(offsetof(Vertex, mNormal)));

	glBindVertexArray(0);

	mIndexBuffer.unbind();
	mVertexBuffer.unbind();


	glBindVertexArray(0);

}

void RenderableHandlerOpenGL::bind()
{
	glBindVertexArray(mVertexArray);

}

void RenderableHandlerOpenGL::render()
{

	glBindVertexArray(mVertexArray);
	//mIndexBuffer.bind();
	glDrawElements(mPrimitiveType,
		static_cast<GLsizei>(mIndexCount),
		GL_UNSIGNED_INT,
		nullptr);
	//mIndexBuffer.unbind();
	glBindVertexArray(0);
}

void RenderableHandlerOpenGL::unbind()
{
	glBindVertexArray(0);

}
