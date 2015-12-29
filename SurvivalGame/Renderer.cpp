#include <GL\glew.h>
#include <GLFW\glfw3.h>
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

CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
}

void CRenderer::InitDependencies()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void CRenderer::Render()
{
	ClearFrame();
	MeshPass();
}

void CRenderer::MeshPass()
{
	glm::mat4 vp = gSys->pGame->pCamera->GetVPMatrix();
	for (std::pair<unsigned int, IMesh*> it : gSys->pEngine->pMeshSystem->GetMeshContainer())
	{
		IMesh* pMesh = it.second;
		glBindVertexArray(pMesh->GetVertexArray());
		glUseProgram(pMesh->GetShader()->GetProgramId());
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[MVP], 1, GL_FALSE, glm::value_ptr(vp*pMesh->GetModelMatrix()));
		glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[OBJ2WORLD], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));
		glDrawElements(GL_TRIANGLES, pMesh->GetIndexCount() * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
	}
}

void CRenderer::ClearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2,0.2,0.9,1);
}
