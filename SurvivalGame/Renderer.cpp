#include "SSAO.h"
#include "Renderer.h"
#include "GlobalSystem.h"
#include "IMesh.h"
#include "StaticMesh.h"
#include "Engine.h"
#include "MeshSystem.h"
#include "Shader.h"
#include "Game.h"
#include "Camera.h"
#include <glm\gtc\type_ptr.hpp>
#include "Pipeline.cc"
#include "PointLight.h"

CRenderer::~CRenderer()
{
	delete m_pGBuffer;
	delete m_pSSAO;
	delete m_pLightSystem;
	delete m_radianceGen;
	delete m_pSkybox;
}
bool a = true;
void CRenderer::InitDependencies()
{
	m_pGBuffer = new CGBuffer;
	m_pSSAO = new CSSAO;
	m_pLightSystem = new CLightSystem;
	m_radianceGen = new CRadianceGen;
	m_pSkybox = new CSkyBox;

}

void CRenderer::Render()
{
	if (a)
	{
		m_radianceGen->Render();
		a = false;
	}
	m_pGBuffer->Begin();
	ClearFrame();
	MeshPass();
	m_pLightSystem->DrawLights();
	m_pGBuffer->RenderQuad();
}

void CRenderer::MeshPass()
{
	m_pGBuffer->MeshPass();
	glm::mat4 v = gSys->pGame->pCamera->GetViewMatrix();
	glm::mat4 p = gSys->pGame->pCamera->GetProjectionMatrix();
	for (std::pair<unsigned int, IMesh*> it : gSys->pEngine->pMeshSystem->GetMeshContainer())
	{
		IMesh* pMesh = it.second;
		Pipeline::draw_begin(pMesh->GetVertexArray(), pMesh->GetShader()->GetProgramId());

		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(p));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[OBJ2WORLD], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));

		if (pMesh->GetTexture() != nullptr)
			pMesh->GetTexture()->ActivateTexture(GL_TEXTURE10, pMesh->GetShader()->GetUniforms()[TEXTURESAMPLER]);

		Pipeline::draw_end(pMesh->GetIndexCount(), GL_TRIANGLES);
	}
	m_pSkybox->Draw();
}

void CRenderer::ClearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1);
}
