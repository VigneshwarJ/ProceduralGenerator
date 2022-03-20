#include "RendererOpenGL.h"

#include "RenderableHandlerOpenGL.h"
#include "TextureHandlerOpenGL.h"
#include "BufferObjectOpenGL.h"
#include "../../Scenegraph/StaticShaderCode.h"

RendererOpenGL::RendererOpenGL()
{
}

RendererOpenGL::~RendererOpenGL()
{
}

void RendererOpenGL::initializeDefaultShaderLibrary()
{
	ShaderHandlerOpenGLSharedPtr default_shader
		= std::make_shared<ShaderHandlerOpenGL>();
	default_shader->addShaderFromSourceCode(
		ShaderHandlerOpenGL::VERTEX_SHADER,
		default_vertex_shader);
	default_shader->addShaderFromSourceCode(
		ShaderHandlerOpenGL::FRAGMENT_SHADER,
		default_fragment_shader);
	default_shader->link();
	mShaderLibrary[PG_DEFAULT_SHADER] = default_shader;

	default_shader->bindShader();
	default_shader->setUniformFloat("u_textureFlag", 0.0f);
	default_shader->unbindShader();
}

void RendererOpenGL::initialize()
{
	initializeDefaultShaderLibrary();

	mPrimitiveTypeMap[PG_TRIANGLES] = GL_TRIANGLES;
	mPrimitiveTypeMap[PG_TRIANGLE_STRIP] = GL_TRIANGLE_STRIP;
}

IRenderableHandlerSharedPtr RendererOpenGL::generatePolygonalGeometryHandler(
	const Vertex* p_vertices,
	const uint32_t* p_indices,
	std::size_t number_of_vertices,
	std::size_t number_of_indices,
	GLenum primitive_type)
{
	RenderableHandlerOpenGLSharedPtr buffer_handler
		= std::make_shared<RenderableHandlerOpenGL>();
	buffer_handler->initialize(
		p_vertices,
		p_indices,
		number_of_vertices,
		number_of_indices,
		primitive_type);
	return buffer_handler;
}

ITextureHandlerSharedPtr RendererOpenGL::generateTextureHandler(
	const std::string& texture_file_path)
{
	TextureHandlerOpenGLSharedPtr texture_handler
		= std::make_shared<TextureHandlerOpenGL>(texture_file_path);
	return texture_handler;
}

IBufferObjectSharedPtr RendererOpenGL::generateBufferObject(
	const glm::vec4* p_per_vertex_color,
	size_t number_of_vertices)
{
	BufferObjectOpenGLSharedPtr per_vertex_data_handler
		= std::make_shared<BufferObjectOpenGL>();
	per_vertex_data_handler->setBufferData(p_per_vertex_color,
		number_of_vertices);
	return per_vertex_data_handler;
}

GLenum RendererOpenGL::getNativePrimitiveType(PrimitiveType type)
{
	return mPrimitiveTypeMap[type];
}

IShaderHandlerSharedPtr RendererOpenGL::getShaderHandler(ShaderProgramType type)
{
	return mShaderLibrary[type];
}
