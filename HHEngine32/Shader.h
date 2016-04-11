#pragma once
#include "IShader.h"
#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

enum
{
	MODELMAT, VIEWMAT, TEXTURESAMPLER, OBJ2WORLD, gCOLOR, gNORMAL, gPOS, gDEPTH, gDEPTHPOS, gVIEWNORMAL, gLIGHTBUFFER, WIDTH, HEIGHT, SSAOKERNEL, SSAORADIUS, PROJMAT, NOISETEXTURE, LIGHTCOLOR, LIGHTPOS, LIGHTATT, SHR, SHG, SHB, DEPTHBIASMVP, SHADOWMAP
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
	std::string LoadFile(std::string file);
	std::vector<GLuint> m_uniformLocations;
	void GenerateUniformLocations();
	GLuint m_program;
};
