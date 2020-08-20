#include "Terrain.h"
float Terrain::SIZE = 800;
int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int GridX, int GridZ, Texture* texture):
	x(GridX*SIZE),
	z(GridZ*SIZE)
{
	proceduralTerrain(texture);
}

Terrain::~Terrain()
{
	delete mesh;
}

void Terrain::proceduralTerrain(Texture* texture)
{
		int count = VERTEX_COUNT * VERTEX_COUNT;
		int indexSize = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);

		float vertices[128* 128* 3];
		float normals[128 * 128 * 3];
		float textureCoords[128 * 128 * 2];
		unsigned int* indices = new unsigned int[indexSize];
		int vertexPointer = 0;
		for (int i = 0; i < VERTEX_COUNT; i++) {
			for (int j = 0; j < VERTEX_COUNT; j++) {
				vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
				vertices[vertexPointer * 3 + 1] = 0;
				vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
				normals[vertexPointer * 3] = 0;
				normals[vertexPointer * 3 + 1] = 1;
				normals[vertexPointer * 3 + 2] = 0;
				textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
				textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
				vertexPointer++;
			}
		}
		int pointer = 0;
		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				int topLeft = (gz * VERTEX_COUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}
		//Texture* texture = nullptr;
		//		System.out.println("reached here Terrain Generation");

		this->mesh = new Mesh(vertices, indices,textureCoords, normals, 
			count, indexSize, count , count,texture);

		/*vertices;
		normals;
		textureCoords;*/

		//return mesh;
	
}

Mesh* Terrain::getModel()
{
	return mesh;
}

float Terrain::getX()
{
	return x;
}

float Terrain::getZ()
{
	return z;
}
