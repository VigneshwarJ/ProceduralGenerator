#include "DiffuseMaterial.h"




DiffuseMaterial::DiffuseMaterial()
{
}

DiffuseMaterial::~DiffuseMaterial()
{
}

void DiffuseMaterial::setColorPerVertex(
	const glm::vec4* p_per_vertex_color,
	size_t number_of_vertices)
{
	mpPerVertexColor = p_per_vertex_color;
	mNumberOfVertices = number_of_vertices;
}

void DiffuseMaterial::setColorPerVertexHandler(
	IBufferObjectSharedPtr color_handler)
{
	mColorDataHandler = color_handler;
}

const glm::vec4* DiffuseMaterial::getColorPerVertex()
{
	return mpPerVertexColor;
}

size_t DiffuseMaterial::getNumberOfVertices()
{
	return mNumberOfVertices;
}

IBufferObjectSharedPtr DiffuseMaterial::getColorPerVertexHandler()
{
	return mColorDataHandler;
}

void DiffuseMaterial::bindMaterialProperties()
{

}

void DiffuseMaterial::unbindMaterialProperties()
{
}
