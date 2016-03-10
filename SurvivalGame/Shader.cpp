#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <io.h>
#include "GlobalSystem.h"
#include "Utils.hpp"

CShader::CShader(std::string file)
{
	
	auto shadercont = LoadFile(file);


	std::vector<std::string> shaders = StringTools::SplitString(shadercont, '@');
	std::string vertex_content = shaders[0];
	std::string fragment_content = shaders[1];

	auto splitFragContent = StringTools::SplitString(shaders[1], '$');

	if (splitFragContent.size() > 1)
	{
		fragment_content = splitFragContent[0] +"\n"+ LoadFile(splitFragContent[1]) + "\n" + splitFragContent[2];
	}

	const char* v = vertex_content.c_str();
	const char* f = fragment_content.c_str();

	//Create shaders.

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &v, NULL);
	glCompileShader(vs);
	GLint s;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &s);
	if (!s)
	{
		gSys->Log(std::string("Error compiling vert shader "+file),this);
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &f, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &s);
	if (!s)
	{
		gSys->Log(std::string("Error compiling frag shader " + file), this);
	}

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &s);

	if (s == GL_FALSE)
	{
		GLint maxSize;
		glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &maxSize);

		std::vector<char> log(maxSize);
		glGetProgramInfoLog(shader_programme, maxSize, &maxSize, &log[0]);
		printf(log.data());
	}

	m_program = shader_programme;

	glDeleteShader(vs);
	glDeleteShader(fs);

	GenerateUniformLocations();
}

CShader::~CShader()
{
	glDeleteProgram(m_program);
}

std::string CShader::LoadFile(std::string file)
{
	std::ifstream shader_stream(file.c_str());

	std::string shadercont = "";

	if (!shader_stream.is_open())
	{
		gSys->Log("Error loading file: "+file, this);
	}

	std::string line = "";
	while (!shader_stream.eof())
	{
		std::getline(shader_stream, line);
		shadercont.append(line + "\n");
	}

	line = "";

	shader_stream.close();

	return shadercont;
}

void CShader::GenerateUniformLocations()
{
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_modelMat"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_viewMat"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_texSampler"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_2world"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gColor"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gNormal"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gPos"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gDepth"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gViewPosDepth"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gViewNormal"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_gLightTexture"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_width"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_height"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_ssaoKernel"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_ssaoRadius"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_projMat"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_noiseTexture"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_lightColor"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_lightPos"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_lightAtt"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_shR"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_shG"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_shB"));
}