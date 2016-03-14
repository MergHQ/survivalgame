#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>

struct ITexture
{
	virtual ~ITexture() {}
	virtual void ActivateTexture(GLuint activate, GLuint uniformLoc) = 0;
	virtual GLuint& GetTextureId() = 0;
	virtual std::string GetFileName() = 0;
};