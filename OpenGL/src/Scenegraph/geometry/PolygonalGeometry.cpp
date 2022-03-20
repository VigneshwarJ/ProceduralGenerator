#include "PolygonalGeometry.h"


PolygonalGeometry::PolygonalGeometry()
{
}

PolygonalGeometry::~PolygonalGeometry()
{
}

void PolygonalGeometry::setPrimitiveType(PrimitiveType type)
{
	mPrimitiveType = type;
}

void PolygonalGeometry::setVertices(const Vertex* p_vertices,
	std::size_t number_of_vertices)
{
	mpVertices = p_vertices;
	mNumberOfVertices = number_of_vertices;
}

void PolygonalGeometry::setIndices(const uint32_t* p_indices,
	std::size_t number_of_indices)
{
	mpIndices = p_indices;
	mNumberOfIndices = number_of_indices;
}

PrimitiveType PolygonalGeometry::getPrimitiveType()
{
	return mPrimitiveType;
}

const Vertex* PolygonalGeometry::getVertices()
{
	return mpVertices;
}

const uint32_t* PolygonalGeometry::getIndices()
{
	return mpIndices;
}

std::size_t PolygonalGeometry::getNumberOfVertices()
{
	return mNumberOfVertices;
}

std::size_t PolygonalGeometry::getNumberOfIndices()
{
	return  mNumberOfIndices;
}
