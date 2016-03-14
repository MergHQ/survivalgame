#pragma once
#include "noiseutils.h"
#include <glm\vec3.hpp>

class CTerrainGen
{
public:
	CTerrainGen();
	~CTerrainGen();

	void GenerateTerrain(int x, int y,float,float,float,float);
	float GetTerrainHeight(int x, int y);
	float barryCentric(glm::vec3& p1, glm::vec3&  p2, glm::vec3&  p3, glm::vec3&  pos);
private:
	void CreateWater();
	utils::NoiseMap m_heightMap;
	float m_ubound;
	int width, height;
	float** m_heights;
};

