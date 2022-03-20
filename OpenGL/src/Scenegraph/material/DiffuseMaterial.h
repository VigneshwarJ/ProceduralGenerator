#ifndef PG_DIFFUSEMATERIAL_H
#define PG_DIFFUSEMATERIAL_H

#include <vector>

#include "IMaterial.h"
#include "../../Renderer/IBufferObject.h"


MAKE_SHARED(DiffuseMaterial);
class DiffuseMaterial : public IMaterial
{
public:
	DiffuseMaterial();
	~DiffuseMaterial() override;

	void setColorPerVertex(const glm::vec4* p_per_vertex_color,
		size_t number_of_vertices);
	void setColorPerVertexHandler(IBufferObjectSharedPtr color_handler);
	const glm::vec4* getColorPerVertex();
	size_t getNumberOfVertices();
	IBufferObjectSharedPtr getColorPerVertexHandler();

protected:
	void bindMaterialProperties() override;
	void unbindMaterialProperties() override;

private:
	const glm::vec4* mpPerVertexColor;
	size_t mNumberOfVertices;
	IBufferObjectSharedPtr mColorDataHandler;
};

// namespace PG
#endif // PG_DIFFUSEMATERIAL_H
