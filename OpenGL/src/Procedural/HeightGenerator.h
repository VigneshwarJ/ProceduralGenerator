#pragma once
#define _USE_MATH_DEFINES
class HeightGenerator
{
private:
	static float AMPLITUDE;
	static long seed;
	HeightGenerator();
public:

	static float generateHeight(int x, int z, int gridx, int gridy);
	static float getSmoothNoise(int x, int z);
	static float getNoise(int x, int z);
	static float getNoise1(int x, int z);

	static float interpolate(float a, float b, float blend);
	static float getInterpolatedNoise(float x, float y);


};

