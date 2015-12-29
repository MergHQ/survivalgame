#pragma once
#include "IMesh.h"

class CStaticMesh : public IMesh
{
public:
	CStaticMesh(std::string name);
	~CStaticMesh();

	virtual unsigned int GetMeshId() { return m_meshId; }
	virtual unsigned int& GetVertexAttribArray() { return m_vao; }
	virtual std::string GetFileName() { return m_fileName; }
private:
	unsigned int m_meshId;
	std::string m_fileName;
	unsigned int m_vao;
};

