
#include "glm.hpp"
#include "HeightGenerator.h"
#include "../utilities/SmartTypePtr.h"
MAKE_SHARED(SceneItem);
class Terrain
{
private:
	static float SIZE;
	static int VERTEX_COUNT;
	float x;
	float z;
	int GX;
	int GY;

public:
	Terrain(int GridX, int GridZ);
	SceneItemSharedPtr proceduralTerrain();
	~Terrain();
	float getX();
	float getZ();
	float getHeight(int x, int z);
	glm::vec3 getNormals(int x, int z);
};

