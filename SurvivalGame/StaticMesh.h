#pragma once
#include "IMesh.h"
#include "MeshSystem.h"
#include <glm\vec3.hpp>

class CStaticMesh : public IMesh
{
public:
	CStaticMesh(std::string name, IShader* pShader, SMeshData& data = SMeshData());
	~CStaticMesh();

	// IMesh
	virtual unsigned int GetMeshId() { return m_meshId; }
	virtual GLuint& GetVertexArray() { return m_vao; }
	virtual std::string GetFileName() { return m_fileName; }
	virtual IShader* GetShader() { return m_pShader; }
	virtual glm::mat4& GetModelMatrix() { return m_modelMatrix; }
	virtual size_t& GetIndexCount() { return m_indexCount; }
	virtual void SetPosition(glm::vec3& pos);
	virtual glm::vec3& GetPosition() { return m_pos; }
	// ~IMesh

private:
	void BuildMatrix(glm::vec3& position);
	glm::mat4 m_modelMatrix;
	IShader* m_pShader;
	unsigned int m_meshId;
	std::string m_fileName;
	unsigned int m_vao;
	size_t m_indexCount;
	glm::vec3 m_pos;
};

