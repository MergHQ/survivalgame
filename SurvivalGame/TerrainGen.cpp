#include "TerrainGen.h"
#include <noise\noise.h>
#include "MeshSystem.h"
#include "GlobalSystem.h"
#include "Engine.h"
#include "MeshSystem.h"
#include "noiseutils.h"
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\geometric.hpp>
#include <random>

CTerrainGen::CTerrainGen()
{
}

CTerrainGen::~CTerrainGen()
{
}

void CTerrainGen::GenerateTerrain(int x, int y, float lxb, float uxb, float lyb, float uyb)
{
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	std::vector<float> texcoords;

	m_ubound = uyb;
	width = x;
	height = y;
	noise::module::Perlin perlinNoise;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 103453859043);
	perlinNoise.SetSeed(dist(rd));
	perlinNoise.SetFrequency(0.2);
	perlinNoise.SetOctaveCount(20);
	heightMapBuilder.SetSourceModule(perlinNoise);
	heightMapBuilder.SetDestNoiseMap(m_heightMap);
	heightMapBuilder.SetDestSize(x, y);
	heightMapBuilder.SetBounds(lxb,uxb,lyb,uyb);
	heightMapBuilder.Build();

	// Cancer.
	for (float i = 0; i < x; i++)
	{
		for (float j = 0; j < y; j++)
		{
			positions.push_back(i - x / 2);
			positions.push_back(m_heightMap.GetValue(i, j) * uyb);
			positions.push_back(j - x / 2);

			Vec2 p = Vec2(i, j);
			float hl = m_heightMap.GetValue(p.x - 1, p.y) * uyb;
			float hr = m_heightMap.GetValue(p.x + 1, p.y) * uyb;
			float hd = m_heightMap.GetValue(p.x, p.y - 1) * uyb;
			float hu = m_heightMap.GetValue(p.x, p.y + 1) * uyb;

			Vec3 norm;
			norm.x = hl - hr;
			norm.y = 2.0f;
			norm.z = hd - hu;
			norm = glm::normalize(norm);


			normals.push_back(norm.x);
			normals.push_back(norm.y);
			normals.push_back(norm.z);

			texcoords.push_back(0);
			texcoords.push_back(0);
		}
	}

	for (float i = 0; i < x-1; i++)
		for (float j = 0; j < y-1; j++)
		{
			int topLeft = (i*x) + j;
			int topRight = topLeft + 1;
			int bottomLeft = ((i + 1)*x) + j;
			int bottomRight = bottomLeft + 1;
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}

	SMeshData data;
	data.indices = indices;
	data.normals = normals;
	data.positions = positions;
	data.texcoord = texcoords;
	gSys->pEngine->pMeshSystem->CreateMesh("", "data/terrain.fx", data);
	CreateWater();
}

float CTerrainGen::GetTerrainHeight(int x, int y)
{
	return m_heightMap.GetValue(x+width/2, y+height/2) * m_ubound;
}

void CTerrainGen::CreateWater()
{
	SMeshData data;
	data.positions = {-10000, 0, -10000, -10000, 0, 10000, 10000, 0, 10000, 10000, 0, -10000};
	data.normals = {0,1,0,0,1,0,0,1,0,0,1,0};
	data.indices = {0,1,2,0,2,3};
	data.texcoord = {0,1,1,0};
	
	gSys->pEngine->pMeshSystem->CreateMesh("", "data/water.fx", data);
}
