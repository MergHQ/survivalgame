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
	std::ifstream shader_stream(file.c_str());

	std::string shadercont = "";

	if (!shader_stream.is_open())
	{
		gSys->Log("Error loading shader file.", this);
	}

	std::string line = "";
	while (!shader_stream.eof())
	{
		std::getline(shader_stream, line);
		shadercont.append(line + "\n");
	}

	line = "";

	shader_stream.close();

	std::vector<std::string> shaders = Split(shadercont, '@');
	const char* vertex_content = shaders[0].c_str();
	const char* fragment_content = shaders[1].c_str();

	//Create shaders.

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_content, NULL);
	glCompileShader(vs);
	GLint s;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &s);
	if (!s)
	{
		gSys->Log(std::string("Error compiling vert shader "+file),this);
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_content, NULL);
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

void CShader::GenerateUniformLocations()
{
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_mvp"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_texSampler"));
	m_uniformLocations.push_back(glGetUniformLocation(m_program, "u_2world"));
}