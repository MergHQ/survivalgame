#include "stdafx.h"
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

IMesh* CMeshSystem::CreateMesh(std::string mesh, std::string shader, SMeshData& data, std::string texture)
{
	if (mesh == "")
	{
		IMesh* m = new CStaticMesh("", shader, texture, m_nextId, data);
		m_meshContainer[m_nextId] = m;
		m_nextId++;
	}
	else
	{
		IMesh* m = new CStaticMesh(mesh, shader, texture, m_nextId);
		m_meshContainer[m_nextId] = m;
		m_nextId++;

		return m;
	}
	return nullptr;
}

void CMeshSystem::PurgeMesh(IMesh *m)
{
	m_meshContainer.erase(m->GetMeshId());
	delete m;
}
