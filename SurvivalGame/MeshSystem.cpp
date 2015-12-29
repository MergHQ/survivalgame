#include "MeshSystem.h"
#include "StaticMesh.h"
#include "Shader.h"

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

IMesh* CMeshSystem::CreateMesh(std::string mesh, std::string shader, SMeshData& data)
{
	if (mesh == "")
	{
		IMesh* m = new CStaticMesh("", new CShader(shader), data);
		m_meshContainer[m_nextId] = m;
		m_nextId++;
	}
	else
	{
		IMesh* m = new CStaticMesh(mesh, new CShader(shader));
		m_meshContainer[m_nextId] = m;
		m_nextId++;

		return m;
	}
	return nullptr;
}
