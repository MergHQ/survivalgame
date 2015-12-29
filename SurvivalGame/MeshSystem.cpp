#include "MeshSystem.h"
#include "StaticMesh.h"

CMeshSystem::CMeshSystem()
{
}

CMeshSystem::~CMeshSystem()
{
	for (std::pair<uint32_t, IMesh*> e : m_meshContainer)
	{
		delete e.second;
	}
}

IMesh* CMeshSystem::CreateMesh(std::string mesh)
{
	IMesh* m = new CStaticMesh(mesh);
	m_meshContainer[m_nextId] = m;
	m_nextId++;

	return m;
}
