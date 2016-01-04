#pragma once
#include "noiseutils.h"
#include <vector>

class CTerrainGen
{
public:
	CTerrainGen();
	~CTerrainGen();

	void GenerateTerrain(int x, int y,float,float,float,float);
	float GetTerrainHeight(int x, int y);
private:
	void CreateWater();
	utils::NoiseMap m_heightMap;
	float m_ubound;
	int width, height;
};

