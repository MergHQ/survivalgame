#include "stdafx.h"
#include "SSAO.h"
#include "Renderer.h"
#include "GlobalSystem.h"
#include "IMesh.h"
#include "StaticMesh.h"
#include "Engine.h"
#include "MeshSystem.h"
#include "Shader.h"
#include "CameraSystem.h"
#include <glm\gtc\type_ptr.hpp>
#include "Pipeline.cc"
#include "PointLight.h"
#include "EnvironmentProbe.h"

CRenderer::~CRenderer()
{
	delete m_pGBuffer;
	delete m_pSSAO;
	delete m_pLightSystem;
	delete m_radianceGen;
	delete m_pSkybox;
	delete m_pEnvProbe;
}

void CRenderer::InitDependencies()
{
	m_pGBuffer = new CGBuffer;
	m_pSSAO = new CSSAO;
	m_pLightSystem = new CLightSystem;
	m_radianceGen = new CRadianceGen;
	m_pSkybox = new CSkyBox;
	m_pEnvProbe = new CEnvironmentProbe;
	m_pEnvProbe->SetLightPosition(glm::vec3(0, 10, 0));
	m_pEnvProbe->Update();
}

void CRenderer::Render()
{
	m_pGBuffer->Begin();
	ClearFrame();
	MeshPass();
	m_pLightSystem->DrawLights();
	m_pGBuffer->RenderQuad();
}

void CRenderer::MeshPass()
{
	// Yeah, we can't do shit without a camera.
	if (!gSys->pEngine->pCamSys->GetCurrentCamera())
		return;

	CMeshSystem* pMeshSys = gSys->pEngine->pMeshSystem;
	// Why should we even run this if there is nothing to render?
	if (!pMeshSys)
		return;

	m_pGBuffer->MeshPass();
	glm::mat4 v = gSys->pEngine->pCamSys->GetCurrentCamera()->GetViewMatrix();
	glm::mat4 p = gSys->pEngine->pCamSys->GetCurrentCamera()->GetProjectionMatrix();
	for (std::pair<unsigned int, IMesh*> it : pMeshSys->GetMeshContainer())
	{
		IMesh* pMesh = it.second;
		Pipeline::draw_begin(pMesh->GetVertexArray(), pMesh->GetShader()->GetProgramId());

		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(p));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[OBJ2WORLD], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));

		if(((CSun*)m_pLightSystem->GetSun())->GetShadowMap())
			glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[DEPTHBIASMVP], 1, GL_FALSE,
				glm::value_ptr(((CSun*)m_pLightSystem->GetSun())->GetShadowMap()->GetDepthBiasMVP()));

		((CSun*)m_pLightSystem->GetSun())->GetShadowMap()->GetShadowMap()->ActivateTexture(GL_TEXTURE11, 
			pMesh->GetShader()->GetUniforms()[SHADOWMAP]);

		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[SHR], 1, GL_FALSE, glm::value_ptr(m_pEnvProbe->shValues_r));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[SHG], 1, GL_FALSE, glm::value_ptr(m_pEnvProbe->shValues_g));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[SHB], 1, GL_FALSE, glm::value_ptr(m_pEnvProbe->shValues_b));

		if (pMesh->GetTexture() != nullptr)
			pMesh->GetTexture()->ActivateTexture(GL_TEXTURE10, pMesh->GetShader()->GetUniforms()[TEXTURESAMPLER]);

		Pipeline::draw_end(pMesh->GetIndexCount(), GL_TRIANGLES);
	}
	m_pSkybox->Draw();
	((CSun*)m_pLightSystem->GetSun())->Update();
}

void CRenderer::ClearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1);
}
