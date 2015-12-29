#include "TerrainGen.h"
#include <noise\noise.h>
#include "MeshSystem.h"
#include "GlobalSystem.h"
#include "Engine.h"
#include "MeshSystem.h"
#include "noiseutils.h"
#include <glm\vec2.hpp>
#include <glm\geometric.hpp>

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

	noise::module::Perlin perlinNoise;
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	perlinNoise.SetSeed(rand() % 10432594039);
	heightMapBuilder.SetSourceModule(perlinNoise);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(x, y);
	heightMapBuilder.SetBounds(lxb,uxb,lyb,uyb);
	heightMapBuilder.Build();

	// Cancer.
	for (float i = 0; i < x; i++)
		for (float j = 0; j < y; j++)
		{
			positions.push_back(i);
			positions.push_back(heightMap.GetValue(i, j) * uyb);
			positions.push_back(j);
			glm::vec2 p = glm::vec2(i, j);
			float hl = heightMap.GetValue(p.x - 1 ,p.y) * uyb;
			float hr = heightMap.GetValue(p.x + 1, p.y) * uyb;
			float hd = heightMap.GetValue(p.x, p.y - 1) * uyb;
			float hu = heightMap.GetValue(p.x, p.y + 1) * uyb;

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
	gSys->pEngine->pMeshSystem->CreateMesh("", "data/basic.fx", data);
}
