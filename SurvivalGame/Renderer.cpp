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
#include "PointLight.h"

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
	delete m_pGBuffer;
	delete m_pSSAO;
	delete m_pLightSystem;
	delete m_radianceGen;
}
void CRenderer::InitDependencies()
{
	m_pGBuffer = new CGBuffer;
	m_pSSAO = new CSSAO;
	m_pLightSystem = new CLightSystem;
	m_radianceGen = new CRadianceGen;
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
	m_pGBuffer->MeshPass();
	glm::mat4 v = gSys->pGame->pCamera->GetViewMatrix();
	glm::mat4 p = gSys->pGame->pCamera->GetProjectionMatrix();
	for (std::pair<unsigned int, IMesh*> it : gSys->pEngine->pMeshSystem->GetMeshContainer())
	{
		IMesh* pMesh = it.second;
		glBindVertexArray(pMesh->GetVertexArray());
		glUseProgram(pMesh->GetShader()->GetProgramId());

		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(p));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[OBJ2WORLD], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));

		if (pMesh->GetTexture() != nullptr)
			pMesh->GetTexture()->ActivateTexture(GL_TEXTURE10, pMesh->GetShader()->GetUniforms()[TEXTURESAMPLER]);

		glDrawElements(GL_TRIANGLES, pMesh->GetIndexCount() * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
	}
}

void CRenderer::ClearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5,0.5,0.8,1);
}
