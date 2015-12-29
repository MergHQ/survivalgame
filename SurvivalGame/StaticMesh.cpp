#include "StaticMesh.h"
#include "tiny_obj_loader.h"
#include <GLFW\glfw3.h>
#include <GL\glew.h>
#include "GlobalSystem.h"

CStaticMesh::CStaticMesh(std::string file)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, file.c_str());

	if (!err.empty())
	{
		gSys->Log("Cannot find the .obj file specified.",this);
		m_vao = 0;
	}

	GLuint vbo = 0, indicies = 0, normals = 0, texcoords = 0;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	auto shape = shapes[0].mesh;

	if (!shape.positions.empty() || !shape.normals.empty() || !shape.texcoords.empty())
	{
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * shape.positions.size(), &shape.positions[0], GL_STATIC_DRAW);
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
}

CStaticMesh::~CStaticMesh()
{
	glDeleteBuffers(1, &m_vao);
}