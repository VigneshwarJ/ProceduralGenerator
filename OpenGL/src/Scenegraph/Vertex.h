#ifndef PG_VERTEX_H
#define PG_VERTEX_H
#include <glm.hpp>

struct Vertex
{
	Vertex() :
		mPosition(0.0f, 0.0f, 0.0f),
		mTextureCoordinate(0.0f, 0.0f),
		mNormal(0.0f, 0.0f, 0.0f)
	{
	}

	Vertex(glm::vec3 position,
		glm::vec2 texture_coordinate,
		glm::vec3 normal) :
		mPosition(position),
		mTextureCoordinate(texture_coordinate),
		mNormal(normal)
	{
	}

	glm::vec3 mPosition;
	glm::vec2 mTextureCoordinate;
	glm::vec3 mNormal;
};

#endif // PG_VERTEX_H
