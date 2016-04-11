#include "stdafx.h"
#include "SkyBox.h"
#include "Shader.h"
#include "StaticMesh.h"
#include <GLFW\glfw3.h>
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\common.hpp>
#include "Texture.h"
#include "Engine.h"
#include "CameraSystem.h"
#include "GlobalSystem.h"

CSkyBox::CSkyBox()
{
	m_pMesh = new CStaticMesh("data/skybox.obj", "data/skybox.fx", "data/blue.png", 120);
}

CSkyBox::~CSkyBox()
{
	delete m_pMesh;
}

void CSkyBox::Draw()
{
	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	glUseProgram(m_pMesh->GetShader()->GetProgramId());

	glBindVertexArray(m_pMesh->GetVertexArray());

	glUniformMatrix4fv(m_pMesh->GetShader()->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(m_pMesh->GetModelMatrix()));
	glUniformMatrix4fv(m_pMesh->GetShader()->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(gSys->pEngine->pCamSys->GetCurrentCamera()->GetViewMatrix()));
	glUniformMatrix4fv(m_pMesh->GetShader()->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(gSys->pEngine->pCamSys->GetCurrentCamera()->GetProjectionMatrix()));

	m_pMesh->GetTexture()->ActivateTexture(GL_TEXTURE20, m_pMesh->GetShader()->GetUniforms()[TEXTURESAMPLER]);

	glDrawElements(GL_TRIANGLES, m_pMesh->GetIndexCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthFuncMode);

	glUseProgram(NULL);
	glActiveTexture(0);
}
