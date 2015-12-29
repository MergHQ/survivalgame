#pragma once
#include "IShader.h"
#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

enum
{
	MVP, TEXTURESAMPLER, OBJ2WORLD
};

class CShader : public IShader
{
public:
	CShader::CShader(std::string file);
	CShader::~CShader();

	// IShader
	virtual GLuint& GetProgramId() { return m_program; }
	virtual std::vector<unsigned int>& GetUniforms() { return m_uniformLocations; }
	// ~IShader

protected:
private:
	std::vector<GLuint> m_uniformLocations;
	void GenerateUniformLocations();
	GLuint m_program;
};
