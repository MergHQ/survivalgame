#include "stdafx.h"
#include "SSAO.h"
#include <random>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "GlobalSystem.h"
#include "Engine.h"
#include "CameraSystem.h"

CSSAO::CSSAO()
{
	std::tr1::mt19937 eng;
	std::tr1::normal_distribution<float> dist(0.f, 1.f);
	m_kernelSize = 64;
	for (int i = 0; i < m_kernelSize; i++)
	{
		glm::vec3 point = glm::vec3(dist(eng) * 2.0 - 1.0, dist(eng) * 2.0-1.0, dist(eng));
		point = glm::normalize(point);
		point *= dist(eng);
		float scale = float(i) / float(m_kernelSize);
		scale = lerp(0.1f, 1.0f, scale*scale);
		point *= scale;

		m_kernelPoints.push_back(point);
	}

	for (GLuint i = 0; i < 16; i++)
	{
		glm::vec3 noise(
			dist(eng) * 2.0 - 1.0,
			dist(eng) * 2.0 - 1.0,
			0.0f);
		m_ssaoNoise.push_back(noise);
	}

	glGenTextures(1, &m_noiseTextureId);
	glBindTexture(GL_TEXTURE_2D, m_noiseTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &m_ssaoNoise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

CSSAO::~CSSAO()
{
}

void CSSAO::SendUniforms(GLuint uniform1, GLuint uniform2, GLuint uniform3, GLuint uniform4)
{
	glUniform3fv(uniform1, m_kernelPoints.size(), reinterpret_cast<GLfloat*>(m_kernelPoints.data()));
	glUniform1f(uniform2, radius);
	glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(gSys->pEngine->pCamSys->GetCurrentCamera()->GetProjectionMatrix()));
	glActiveTexture(GL_TEXTURE20);
	glBindTexture(GL_TEXTURE_2D, m_noiseTextureId);
	glUniform1i(uniform4, 20);
}

