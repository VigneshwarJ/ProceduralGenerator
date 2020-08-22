#include "HeightGenerator.h"
#include <stdlib.h>
#include <iostream>
float HeightGenerator::AMPLITUDE = 70.0f;
long HeightGenerator::seed = UINT32_MAX-10000;

HeightGenerator::HeightGenerator()
{

}

float HeightGenerator::generateHeight(int x, int z, int gridx, int gridy)
{
	float inter = getInterpolatedNoise((x+ gridx)/4.0, (z + gridy)/4.0) * AMPLITUDE;
	float doule = 0.0f;
	//doule = getInterpolatedNoise((x + gridx) / 4.0f, (z + gridy) / 4.0f) * AMPLITUDE / 3.0f;
	float foule = 0.0f;
	foule = getInterpolatedNoise((x + gridx) / 16.0f, (z + gridy) / 16.0f) * AMPLITUDE / 3.0f;
	return inter+doule+foule;
	/*float fNoise = 0.0f;
	float fScaleAcc = 0.0f;
	float fScale = 1.0f;
	int nOctaves = 2;
	int nWidth = 128;
	float fBias = 0.8;
	for (int o = 0; o < nOctaves; o++)
	{
		int nPitch = nWidth >> o;
		int nSampleX1 = (x / nPitch) * nPitch;
		int nSampleY1 = (z / nPitch) * nPitch;

		int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
		int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

		float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
		float fBlendY = (float)(z - nSampleY1) / (float)nPitch;

		float fSampleT = (1.0f - fBlendX) * getNoise(nSampleX1 ,nSampleY1) + fBlendX * getNoise(nSampleX2, nSampleY1);
		float fSampleB = (1.0f - fBlendX) * getNoise(nSampleX1, nSampleY2) + fBlendX * getNoise(nSampleX2, nSampleY2);

		fScaleAcc += fScale;
		fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
		fScale = fScale / fBias;
	}
	return fNoise / fScaleAcc * AMPLITUDE;*/

}
float HeightGenerator::getSmoothNoise(int x, int z)
{
	float sides = (getNoise(x-1, z) + getNoise(x+1, z) + getNoise(x, z-1) + getNoise(x, z+1)) / 8.0f;
	float corners = (getNoise(x - 1, z-1) + getNoise(x + 1, z-1) + getNoise(x-1, z + 1) + getNoise(x-1, z + 1)) / 16.0f;
	float center = getNoise(x, z) / 4.0f;

	return corners+sides+center;
	
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
	float f = (float)(1.0f - cos(theta))*0.5f;
	return a*(1-f) + b*f;
}

float HeightGenerator::getInterpolatedNoise(float x, float y)
{
	int iX = (int)x;
	int iY = (int)y;
	float fragX = x - iX;
	float fragY = y - iY;
	float v1 = getSmoothNoise(x, y);
	float v2 = getSmoothNoise(x+1, y);
	float v3 = getSmoothNoise(x, y+1);
	float v4 = getSmoothNoise(x+1, y+1);
	float f1 = interpolate(v1, v2, fragX);
	float f2= interpolate(v3,v4,fragX);

	return interpolate(f1,f2,fragY);
}
