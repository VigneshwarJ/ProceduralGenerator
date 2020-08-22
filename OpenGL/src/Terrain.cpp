#include "Terrain.h"
#include <iostream>
float Terrain::SIZE = 800;
int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int GridX, int GridZ, Texture* texture) :
	x(GridX* SIZE),
	z(GridZ* SIZE),
	GX(GridX * 127),
	GY(GridZ * 127)
{

	proceduralTerrain(texture);
	ground = new Texture("res/grass2.png");
	grass = new Texture("res/grass.png");
	grass2 = new Texture("res/grass2.png");
}

Terrain::~Terrain()
{
	delete mesh;
}

void Terrain::proceduralTerrain(Texture* texture)
{
	//int count = VERTEX_COUNT * VERTEX_COUNT;
	//int indexSize = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);
	//float vertices[128 * 128 * 3];
	//float normals[128 * 128 * 3];
	//float textureCoords[128 * 128 * 2];
	//unsigned int* indices = new unsigned int[indexSize];
	//int vertexPointer = 0;
	//for (int i = 0; i < VERTEX_COUNT; i++) {
	//	for (int j = 0; j < VERTEX_COUNT; j++) {
	//		vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
	//		float height = getHeight(j, i);
	//		//std::cout << height<<std::endl;
	//		vertices[vertexPointer * 3 + 1] = height;
	//		vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
	//		glm::vec3 normal = getNormals(j, i);
	//		normals[vertexPointer * 3] =normal[0];
	//		normals[vertexPointer * 3 + 1] = normal[1];
	//		normals[vertexPointer * 3 + 2] = normal[2];
	//		/*normals[vertexPointer * 3] = 0;
	//		normals[vertexPointer * 3 + 1] = 1;
	//		normals[vertexPointer * 3 + 2] = 0;*/
	//		textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
	//		textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
	//		vertexPointer++;
	//	}
	//}
	//int pointer = 0;
	//for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
	//	for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
	//		int topLeft = (gz * VERTEX_COUNT) + gx;
	//		int topRight = topLeft + 1;
	//		int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
	//		int bottomRight = bottomLeft + 1;
	//		indices[pointer++] = topLeft;
	//		indices[pointer++] = bottomLeft;
	//		indices[pointer++] = topRight;
	//		indices[pointer++] = topRight;
	//		indices[pointer++] = bottomLeft;
	//		indices[pointer++] = bottomRight;
	//	}
	//}
	int count = VERTEX_COUNT * VERTEX_COUNT;
	//float* heights = new float[VERTEX_COUNT][VERTEX_COUNT];
	float* vertices = new float[count * 3];
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	int* indices = new int[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT * 1)];
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			float height = getHeight(j, i);
			vertices[vertexPointer * 3 + 1] = height;
			//heights[j][i] = height;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			glm::vec3 normal = getNormals(j, i);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
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

	this->mesh = new Mesh(vertices,(unsigned int*) indices, textureCoords, normals,
		count, 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT * 1), count, count, texture);

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

float Terrain::getHeight(int x, int z)
{
	/*float fNoise = 0.0f;
	float fScaleAcc = 0.0f;
	float fScale = 1.0f;
	int nOctaves = 4;
	int nWidth = 128;
	for (int o = 0; o < nOctaves; o++)
	{
		int nPitch = nWidth >> o;
		int nSampleX1 = (x / nPitch) * nPitch;
		int nSampleY1 = (y / nPitch) * nPitch;

		int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
		int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

		float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
		float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

		float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
		float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

		fScaleAcc += fScale;
		fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
		fScale = fScale / fBias;
	}*/



	//std::cout << "generate geight" << HeightGenerator::generateHeight(5, 4) << std::endl;
	float x1 = HeightGenerator::generateHeight(x, z,this->GX, this->GY);
	//std::cout << x1 << std::endl;
	return x1;
}

glm::vec3 Terrain::getNormals(int x, int z)
{
	float NL = HeightGenerator::generateHeight(x - 1, z,  this->GX, this->GY);
	float NR = HeightGenerator::generateHeight(x + 1, z, this->GX, this->GY);
	float ND = HeightGenerator::generateHeight(x, z - 1, this->GX, this->GY);
	float NU = HeightGenerator::generateHeight(x, z + 1, this->GX, this->GY);
	glm::vec3 normal(NL - NR, 2.0f, ND - NU);
	normal = glm::normalize(normal);
	return normal;
}
