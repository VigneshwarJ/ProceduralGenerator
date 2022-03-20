#ifndef PG_RENDEREROPENGL_H
#define PG_RENDEREROPENGL_H

#include <unordered_map>

#include "../../Scenegraph/Vertex.h"
#include "../../Scenegraph/geometry/Renderable.h"
#include "../IRenderableHandler.h"
#include "../ITextureHandler.h"
#include "../IBufferObject.h"
#include "ShaderHandlerOpenGL.h"

namespace std
{
	template <>
	struct hash<ShaderProgramType> {
		size_t operator()(ShaderProgramType x) const {
			return hash<int>()(static_cast<int>(x));
		}
	};
	template <>
	struct hash<PrimitiveType> {
		size_t operator()(PrimitiveType x) const {
			return hash<int>()(static_cast<int>(x));
		}
	};
}


MAKE_SHARED(RendererOpenGL);
class RendererOpenGL
{
public:
	RendererOpenGL();
	~RendererOpenGL();

	void initialize();
	IRenderableHandlerSharedPtr generatePolygonalGeometryHandler(
		const Vertex* p_vertices,
		const uint32_t* p_indices,
		std::size_t number_of_vertices,
		std::size_t number_of_indices,
		GLenum primitive_type);
	ITextureHandlerSharedPtr generateTextureHandler(
		const std::string& texture_file_path);
	// TODO: Need to make generateBufferObject more generic!
	IBufferObjectSharedPtr generateBufferObject(
		const glm::vec4* p_per_vertex_color,
		size_t number_of_vertices);
	GLenum getNativePrimitiveType(PrimitiveType type);
	IShaderHandlerSharedPtr getShaderHandler(ShaderProgramType type);

private:
	void initializeDefaultShaderLibrary();

	std::unordered_map<ShaderProgramType, ShaderHandlerOpenGLSharedPtr>
		mShaderLibrary;
	std::unordered_map<PrimitiveType, GLenum> mPrimitiveTypeMap;
};

#endif // PG_RENDEREROPENGL_H
