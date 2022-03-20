#include "HeightGenerator.h"
#include <stdlib.h>
#include <iostream>
float HeightGenerator::AMPLITUDE = 100.0f;
long HeightGenerator::seed = UINT32_MAX - 10000;

HeightGenerator::HeightGenerator()
{

}

float HeightGenerator::generateHeight(int x, int z, int gridx, int gridy)
{
	float inter = getInterpolatedNoise((x + gridx) / 8.0f, (z + gridy) / 8.0f) * AMPLITUDE;
	float doule = 0.0f;
	//doule = getInterpolatedNoise((x + gridx) / 4.0f, (z + gridy) / 4.0f) * AMPLITUDE / 3.0f;
	float foule = 0.0f;
	foule = getInterpolatedNoise((x + gridx) / 16.0f, (z + gridy) / 16.0f) * AMPLITUDE / 3.0f;
	return inter + doule + foule;

}
float HeightGenerator::getSmoothNoise(int x, int z)
{
	float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1) + getNoise(x, z + 1)) / 8.0f;
	float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1) + getNoise(x - 1, z + 1) + getNoise(x - 1, z + 1)) / 16.0f;
	float center = getNoise(x, z) / 4.0f;

	return corners + sides + center;

}
float HeightGenerator::getNoise(int x, int z)
{
	uint32_t seed = uint32_t(x) * 1087;
	seed ^= 12271334;
	seed += uint32_t(z) * 2749;
	seed ^= 2323245;

	return (float(int(seed % 2001) - 1000) / 1000.0f);

}
float HeightGenerator::getNoise1(int x, int z)
{
	float random = ((float)rand() / (float)RAND_MAX);
	if (random > 1)
	{
		std::cout << "danger" << random << std::endl;
	}
	return (random * 2.0f - 1.0f);
}

float HeightGenerator::interpolate(float a, float b, float blend)
{
	double theta = blend * M_PI;
	float f = (float)(1.0f - cos(theta)) * 0.5f;
	return a * (1 - f) + b * f;
}

float HeightGenerator::getInterpolatedNoise(float x, float y)
{
	int iX = (int)x;
	int iY = (int)y;
	float fragX = x - iX;
	float fragY = y - iY;
	float v1 = getSmoothNoise(iX, iY);
	float v2 = getSmoothNoise(iX + 1, iY);
	float v3 = getSmoothNoise(iX, iY + 1);
	float v4 = getSmoothNoise(iX + 1, iY + 1);
	float f1 = interpolate(v1, v2, fragX);
	float f2 = interpolate(v3, v4, fragX);

	return interpolate(f1, f2, fragY);
}
