#pragma once
#include <string>
#include "IShader.h"
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

struct IMesh
{
	virtual ~IMesh() {};
	virtual unsigned int GetMeshId() = 0;
	virtual GLuint& GetVertexArray() = 0;
	virtual std::string GetFileName() = 0;
	virtual IShader* GetShader() = 0;
	virtual glm::mat4& GetModelMatrix() = 0;
	virtual size_t& GetIndexCount() = 0;
	virtual void SetPosition(glm::vec3& pos) = 0;
	virtual glm::vec3& GetPosition() = 0;
};