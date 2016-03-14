#include "stdafx.h"
#include "StaticMesh.h"
#include "Shader.h"
#include "GlobalSystem.h"
#include <glm\gtc\matrix_transform.hpp>
#include "Engine.h"
#include "ITexture.h"
#include "Texture.h"

CStaticMesh::CStaticMesh(std::string file, std::string shader, std::string texture, unsigned int id, SMeshData& data)
{
	tinyobj::mesh_t shape;
	tinyobj::mesh_t* shapePtr;
	m_meshId = id;
	GLuint vbo = 0, indicies = 0, normals = 0, texcoords = 0;
	bool shouldLoad = true;

	if (file == "")
	{
		shape.indices = data.indices;
		shape.normals = data.normals;
		shape.positions = data.positions;
		shape.texcoords = data.texcoord;
		m_pShader = new CShader(shader);
	}
	else
	{
		for (std::pair<uint32_t, IMesh*> p : gSys->pEngine->pMeshSystem->GetMeshContainer())
		{
			if (p.second->GetFileName() == file)
			{
				shapePtr = &p.second->GetMeshData();
				shape = *shapePtr;
				shouldLoad = false;
				m_pShader = p.second->GetShader();
				m_pTexture = p.second->GetTexture();
				break;
			}
		}

		if (shouldLoad)
		{
			m_pShader = new CShader(shader);
			m_fileName = file;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			std::string err = tinyobj::LoadObj(shapes, materials, file.c_str());

			if (!err.empty())
			{
				gSys->Log("Cannot find the .obj file specified.", this);
			}

			if (shapes.size() != 0)
				shape = shapes[0].mesh;
			else
				gSys->Log("0 shapes loaded.", this);

			m_sharedShape = shape;
		}
	}

	m_vao = 0;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_indexCount = shape.indices.size();

	if (!shape.positions.empty() || !shape.normals.empty() || !shape.texcoords.empty())
	{
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * shape.positions.size(), &shape.positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_FALSE, (GLubyte *)NULL);

		glGenBuffers(1, &indicies);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicies);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices.size() * sizeof(unsigned int), &shape.indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glGenBuffers(1, &normals);
		glBindBuffer(GL_ARRAY_BUFFER, normals);
		glBufferData(GL_ARRAY_BUFFER, shape.normals.size() * sizeof(float), &shape.normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_FALSE, (GLubyte *)NULL);

		glEnableVertexAttribArray(2);
		glGenBuffers(1, &texcoords);
		glBindBuffer(GL_ARRAY_BUFFER, texcoords);
		glBufferData(GL_ARRAY_BUFFER, shape.texcoords.size() * sizeof(float), &shape.texcoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	else
		gSys->Log("One or more of the requried geometry properties are missing. Please check your OBJ file.", this);

	glBindVertexArray(NULL);

	if (texture != "" && shouldLoad)
		m_pTexture = new CTexture(texture);

	m_pos = glm::vec3(1, 1, 1);
	BuildMatrix(m_pos);
}

CStaticMesh::~CStaticMesh()
{
	glDeleteBuffers(1, &m_vao);
	delete m_pShader;
	delete m_pTexture;
}

void CStaticMesh::SetPosition(glm::vec3 & pos)
{
	m_pos = pos;
	BuildMatrix(pos);
}

void CStaticMesh::BuildMatrix(glm::vec3& position)
{
	m_modelMatrix = glm::translate(glm::mat4(), position);
}
