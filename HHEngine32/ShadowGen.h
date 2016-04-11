#pragma once
#include "ITexture.h"
#include "IShader.h"
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>


class CShadowGen
{
public:
	CShadowGen(int w, int h, glm::mat4 projectionMatrix);
	~CShadowGen();

	void ShadowPass(glm::vec3 pos);
	ITexture* GetShadowMap() { return m_pTexture; }
	glm::mat4& GetDepthBiasMVP() { return m_depthBiasMVP; }
private:
	GLuint m_framebuffer;
	ITexture* m_pTexture;
	IShader* m_pSmShader;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_depthBiasMVP;
	int m_width, m_height;
	glm::mat4 m_biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
};

