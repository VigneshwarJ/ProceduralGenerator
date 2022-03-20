#include "Terrain.h"
#include <iostream>
#include "../Scenegraph/geometry/PolygonalGeometry.h"
#include "../Scenegraph/material/TextureMaterial.h"
#include "../Scenegraph/material/DiffuseMaterial.h"
float Terrain::SIZE = 800;
int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int GridX, int GridZ) :
	x(GridX* SIZE),
	z(GridZ* SIZE),
	GX(GridX * 127),
	GY(GridZ * 127)
{

	//ground = new Texture("res/ground.png");
	//grass = new Texture("res/grass.png");
	//slope = new Texture("res/rock.png");
}

Terrain::~Terrain()
{

}

SceneItemSharedPtr Terrain::proceduralTerrain()
{
	int count = VERTEX_COUNT * VERTEX_COUNT;

	std::vector<Vertex>* vertices = new std::vector<Vertex>{};
	std::vector<unsigned int>* indices = new std::vector<unsigned int>{};

	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			Vertex vert{
				glm::vec3{ (float)j / ((float)VERTEX_COUNT - 1) * SIZE,getHeight(j, i),(float)i / ((float)VERTEX_COUNT - 1) * SIZE },
				glm::vec2{(float)j / ((float)VERTEX_COUNT - 1),(float)i / ((float)VERTEX_COUNT - 1)},
				getNormals(j, i) };
			vertices->push_back(vert);
		}
	}
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices->push_back(topLeft);
			indices->push_back(bottomLeft);
			indices->push_back(topRight);
			indices->push_back(topRight);
			indices->push_back(bottomLeft);
			indices->push_back(bottomRight);
		}
	}
	std::vector<glm::vec4>* color = new std::vector<glm::vec4>(vertices->size());
	std::fill(color->begin(), color->end(), glm::vec4(0, 1, 0, 1));
	PolygonalGeometrySharedPtr triangle = std::make_shared<PolygonalGeometry>();

	triangle->setPrimitiveType(PG_TRIANGLES);
	triangle->setVertices(vertices->data(),
		vertices->size());
	triangle->setIndices(indices->data(),
		indices->size());

	DiffuseMaterialSharedPtr diffuse_material
		= std::make_shared<DiffuseMaterial>();
	diffuse_material->setColorPerVertex(color->data(),
		color->size());
	triangle->setMaterial(diffuse_material);
	return triangle;

}

float Terrain::getX()
{
	return x;
}

float Terrain::getZ()
{
	return z;
}

float Terrain::getHeight(int x, int z)
{
	//std::cout << "generate geight" << HeightGenerator::generateHeight(5, 4) << std::endl;
	float x1 = HeightGenerator::generateHeight(x, z, this->GX, this->GY);
	//std::cout << x1 << std::endl;
	return x1;
}

glm::vec3 Terrain::getNormals(int x, int z)
{
	float NL = HeightGenerator::generateHeight(x - 1, z, this->GX, this->GY);
	float NR = HeightGenerator::generateHeight(x + 1, z, this->GX, this->GY);
	float ND = HeightGenerator::generateHeight(x, z - 1, this->GX, this->GY);
	float NU = HeightGenerator::generateHeight(x, z + 1, this->GX, this->GY);
	glm::vec3 normal(NL - NR, 2.0f, ND - NU);
	normal = glm::normalize(normal);
	return normal;
}
