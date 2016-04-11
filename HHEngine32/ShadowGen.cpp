#include "stdafx.h"
#include "ShadowGen.h"
#include "GlobalSystem.h"
#include "Engine.h"
#include "MeshSystem.h"
#include "IMesh.h"
#include "Pipeline.cc"
#include "FboTexture.h"
#include "Shader.h"
#include <glm\gtc\matrix_transform.hpp>
#include "CameraSystem.h"
#include "ICamera.h"

CShadowGen::CShadowGen(int w, int h, glm::mat4 projectionMatrix)
{
	m_height = h;
	m_width = w;
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	m_pTexture = new CFboTexture(GL_DEPTH_COMPONENT16, GL_FLOAT, GL_DEPTH_ATTACHMENT, w, h);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glDrawBuffer(GL_NONE);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		gSys->Log("Failed to create framebuffer.", this);
	}

	m_pSmShader = new CShader("data/shadowmaps.fx");

	m_projectionMatrix = projectionMatrix;
}

CShadowGen::~CShadowGen()
{
	glDeleteFramebuffers(1, &m_framebuffer);
	delete m_pTexture;
	delete m_pSmShader;
}

void CShadowGen::ShadowPass(glm::vec3 pos)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glViewport(0, 0, m_width, m_height);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDrawBuffer(GL_NONE);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	ICamera* pCamera = gSys->pEngine->pCamSys->GetCurrentCamera();
	if (!pCamera)
		return;
	
	glm::mat4 v = glm::lookAt(pos, glm::vec3(0,0,0), glm::vec3(0, 1, 0));

	CMeshSystem* pMeshSys = gSys->pEngine->pMeshSystem;
	if (!pMeshSys)
		return;

	for (std::pair<unsigned int, IMesh*> it : pMeshSys->GetMeshContainer())
	{
		IMesh* pMesh = it.second;
		Pipeline::draw_begin(pMesh->GetVertexArray(), m_pSmShader->GetProgramId());
		glUniformMatrix4fv(m_pSmShader->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));
		glUniformMatrix4fv(m_pSmShader->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(m_pSmShader->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
		m_depthBiasMVP = m_biasMatrix*(m_projectionMatrix*v*pMesh->GetModelMatrix());
		Pipeline::draw_end(pMesh->GetIndexCount(), GL_TRIANGLES);
	}
}
