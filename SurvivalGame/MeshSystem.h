#pragma once
#include <map>
#include "IMesh.h"

class CMeshSystem
{
public:
	CMeshSystem();
	~CMeshSystem();

	IMesh* CreateMesh(std::string mesh);
	IMesh* GetMeshById(unsigned int id) { return m_meshContainer[id]; }

private:
	std::map<unsigned int, IMesh*> m_meshContainer;
	unsigned int m_nextId = 0;
};

