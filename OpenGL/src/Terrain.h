#pragma once
#include "Mesh.h"
#include "HeightGenerator.h"
class Terrain
{
private:
	static float SIZE;
	static int VERTEX_COUNT;
	void proceduralTerrain(Texture* texture);
	float x;
	float z;
	float GX;
	float GY;
	Mesh* mesh;

public:
	Terrain(int GridX,int GridZ,Texture* texture);
	~Terrain();
	Mesh* getModel(); 
	float getX();
	float getZ();
	float getHeight(int x, int z);
	glm::vec3 getNormals(int x, int z);
	Texture* ground;
	Texture* grass;
	Texture* slope;



};

