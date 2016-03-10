#pragma once
#include <map>
#include <vector>
#include "IMesh.h"

struct SMeshData
{
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<uint32_t> indices;
	std::vector<float> texcoord;
};

class CMeshSystem
{
public:
	CMeshSystem();
	~CMeshSystem();

	IMesh* CreateMesh(std::string mesh, std::string shader, SMeshData& data = SMeshData(), std::string texture = "" );
	IMesh* GetMeshById(unsigned int id) { return m_meshContainer[id]; }
	std::map<unsigned int, IMesh*>& GetMeshContainer() { return m_meshContainer; }
	void PurgeMesh(IMesh*);

private:
	std::map<unsigned int, IMesh*> m_meshContainer;
	unsigned int m_nextId = 0;
};

