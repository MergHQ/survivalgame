#include "stdafx.h"
#include "LightSystem.h"
#include "PointLight.h"
#include "Shader.h"
#include "GBuffer.h"
#include "GlobalSystem.h"
#include "Engine.h"
#include "Renderer.h"
#include "CameraSystem.h"
#include "StaticMesh.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

CLightSystem::CLightSystem()
{
	m_pSun = new CSun;
	m_pNullShader = new CShader("data/null.fx");
	lightSphere = new CStaticMesh("data/sphere.obj", "data/pointlight.fx", "", 100);
}

CLightSystem::~CLightSystem()
{
	for (ILight* l : m_lights)
		delete l;

	delete m_pSun;
	delete m_pNullShader;
	delete lightSphere;
}

ILight* CLightSystem::CreatePointLight(glm::vec3 pos, glm::vec3 color)
{
	auto l = new CPointLight(pos, color);
	m_lights.push_back(l);
	return l;
}

void CLightSystem::DrawLights()
{
	gSys->pEngine->pRenderer->GetGBuffer()->StencilPass();

	// Render light spheres for the stencil pass
	glm::mat4 v = gSys->pEngine->pCamSys->GetCurrentCamera()->GetViewMatrix();
	glm::mat4 p = gSys->pEngine->pCamSys->GetCurrentCamera()->GetProjectionMatrix();
	for (ILight* l : m_lights)
	{
		auto castedLight = static_cast<CPointLight*>(l);
		float scale = castedLight->radius;
		glUseProgram(m_pNullShader->GetProgramId());
		glBindVertexArray(lightSphere->GetVertexArray());

		glm::mat4 m = glm::translate(glm::mat4(), l->GetLightPosition()) * glm::scale(glm::mat4(), Vec3(scale, scale, scale));
		glUniformMatrix4fv(m_pNullShader->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(m));
		glUniformMatrix4fv(m_pNullShader->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(m_pNullShader->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(p));
		glDrawElements(GL_TRIANGLES, lightSphere->GetIndexCount() * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
	}

	gSys->pEngine->pRenderer->GetGBuffer()->LightPass();

	for (ILight* l : m_lights)
	{
		auto castedLight = static_cast<CPointLight*>(l);
		float scale = castedLight->radius;
		glUseProgram(lightSphere->GetShader()->GetProgramId());
		glBindVertexArray(lightSphere->GetVertexArray());

		glm::mat4 m = glm::translate(glm::mat4(), l->GetLightPosition()) * glm::scale(glm::mat4(), Vec3(scale, scale, scale));
		glUniformMatrix4fv(lightSphere->GetShader()->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(m));
		glUniformMatrix4fv(lightSphere->GetShader()->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(lightSphere->GetShader()->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(p));

		// G-Buffers
		for (int i = 0; i < gSys->pEngine->pRenderer->GetGBuffer()->GetTextures().size() - 1; i++)
			gSys->pEngine->pRenderer->GetGBuffer()->GetTextures()[i]->ActivateTexture(
				GL_TEXTURE5 + i, lightSphere->GetShader()->GetUniforms()[gCOLOR + i]);

		glUniform1i(lightSphere->GetShader()->GetUniforms()[WIDTH], gSys->pEngine->pRenderer->GetGBuffer()->width);
		glUniform1i(lightSphere->GetShader()->GetUniforms()[HEIGHT], gSys->pEngine->pRenderer->GetGBuffer()->width);

		// Lights
		glUniform3f
			(
			lightSphere->GetShader()->GetUniforms()[LIGHTCOLOR],
			castedLight->GetSetLightColor(glm::vec3(), false).x, castedLight->GetSetLightColor(glm::vec3(), false).y, castedLight->GetSetLightColor(glm::vec3(), false).z
			);
		glUniform3f(
			lightSphere->GetShader()->GetUniforms()[LIGHTPOS],
			castedLight->GetLightPosition().x, castedLight->GetLightPosition().y, castedLight->GetLightPosition().z
			);
		glUniform3f(
			lightSphere->GetShader()->GetUniforms()[LIGHTATT],
			castedLight->GetAttenuation().x, castedLight->GetAttenuation().y, castedLight->GetAttenuation().z
			);
		glDrawElements(GL_TRIANGLES, lightSphere->GetIndexCount() * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
	}

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);
}
