#pragma once
#include "Mesh.h"
class Terrain
{
private:
	static float SIZE;
	static int VERTEX_COUNT;
	void proceduralTerrain(Texture* texture);
	float x;
	float z;
	Mesh* mesh;

public:
	Terrain(int GridX,int GridZ,Texture* texture);
	~Terrain();
	Mesh* getModel(); 
	float getX();
	float getZ();


};

