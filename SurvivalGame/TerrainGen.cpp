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
	std::uniform_int_distribution<int> dist2(0, 1000);
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

			if (dist2(rd) == 1)
			{
				float height = m_heightMap.GetValue(i, j) * uyb + 1;
				if (height > 4.f && height < 19.f)
				{
					auto a = gSys->pEngine->pMeshSystem->CreateMesh("data/test_tree.obj", "data/basic.fx", SMeshData(), "data/untitled.png");
					a->SetPosition(Vec3(i - x / 2, m_heightMap.GetValue(i, j) * uyb + 1, j - x / 2));
				}
			}


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
	//float terrainX = x + width / 2;
	//float terrainZ = y + height / 2;
	//float gridSquareSize = m_heightMap.GetWidth() / ((float)m_heightMap.GetWidth() - 1);
	//int gridX = (int)floor(terrainX / gridSquareSize);
	//int gridZ = (int)floor(terrainZ / gridSquareSize);
	//if (gridX >= m_heightMap.GetWidth() - 1 || gridZ >= m_heightMap.GetWidth() - 1 || gridX < 0 || gridZ < 0)
	//{
	//	return 0;
	//}
	//float xCoord = glm::modf(terrainX, gridSquareSize) / gridSquareSize;
	//float zCoord = glm::modf(terrainZ, gridSquareSize) / gridSquareSize;
	//float answer;
	//if (xCoord <= (1 - zCoord))
	//{
	//	barryCentric(
	//		Vec3(0, m_heightMap.GetHeight(gridX, gridZ), 0),
	//		Vec3(m_heightsX[gridX], m_heightsZ[gridZ+1], 0), 
	//		Vec3(0, m_heightsX[gridX][gridZ + 1], 1),
	//		new Vector2f(xCoord, zCoord));
	//}
	//else
	//{

	//}
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

inline float barryCentric(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
