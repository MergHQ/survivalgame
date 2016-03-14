/*
	Simpe trick to pre-compute global illumination diffuse factor with spherical harmonics.

	I am running the SH interator on a separate thread to make regeneration seamless. I am also planning to do some
	kind of interpolation on the actual sh values to provide a smooth fade between different time of days.

	The speed of the spherical harmonic function is dependent on the size of the environment texture.
	The sample count ís 6*(w*h) where w is the texture width and h is the texture height. 
	For example, a 128x128 pixel texture would need 98304 iterations.
*/

#include "stdafx.h"

// Pre-computed Laplace SH constants.
#define Y0(n)   (0.282095f)                             /* L_00 */
#define Y1(n)   (0.488603f*n.y)                         /* L_1-1 */
#define Y2(n)   (0.488603f*n.z)                         /* L_10 */
#define Y3(n)   (0.488603f*n.x)                         /* L_11 */
#define Y4(n)   (1.092548f*n.x*n.y)                     /* L_2-2 */
#define Y5(n)   (1.092548f*n.y*n.z)                     /* L_2-1 */
#define Y6(n)   (0.315392f*(3.0f*n.z*n.z - 1.0f))       /* L_20 */
#define Y7(n)   (1.092548f*n.x*n.z)                     /* L_21 */
#define Y8(n)   (0.546274f*(n.x*n.x - n.y*n.y))         /* L_22 */

#define RED     0u
#define GREEN   1u
#define BLUE    2u


#include "RadianceGen.h"
#include "GlobalSystem.h"
#include "Engine.h"
#include "Renderer.h"
#include <glm\geometric.hpp>
#include "GBuffer.h"
#include "MeshSystem.h"
#include <glm\gtc\type_ptr.hpp>
#include "Shader.h"
#include <glm\gtc\matrix_transform.hpp>
#include "lodepng.h"

DWORD WINAPI ShThread(void* arguments)
{

	while (true)
	{
		if (gSys->pEngine->pRenderer->GetRadianceGen() && gSys->pEngine->pRenderer->GetRadianceGen()->souldGenerate)
		{
			float shCoeff[3][9];
			memset(shCoeff[RED], 0, 9u*sizeof(float));
			memset(shCoeff[GREEN], 0, 9u*sizeof(float));
			memset(shCoeff[BLUE], 0, 9u*sizeof(float));

			int texRes = 64;
			float texelSize = 1.0f / float(texRes);
			float dColor = 1.0f / float((sizeof(unsigned char) << 8) - 1);   

			const int nc = 3;

			float sumWeight = 0.0f;
			for (int face = 0; face < 6; ++face)
			{
				float u, v;
				unsigned char *pixels = gSys->pEngine->pRenderer->GetRadianceGen()->data[face];

				for (int i = 0; i < texRes; ++i)
				{
					v = 2.0f * ((i + 0.5f) * texelSize) - 1.0f;

					for (int j = 0; j < texRes; ++j)
					{
						u = 2.0f * ((j + 0.5f) * texelSize) - 1.0f;

						glm::vec3 dir; float solidAngle;
						gSys->pEngine->pRenderer->GetRadianceGen()->GetTexelAttrib(face, u, v, texelSize, &dir, &solidAngle);
						sumWeight += solidAngle;

						float lambda;

						lambda = (pixels[RED] * dColor) * solidAngle;
						shCoeff[RED][0] += lambda * Y0(dir);
						shCoeff[RED][1] += lambda * Y1(dir);
						shCoeff[RED][2] += lambda * Y2(dir);
						shCoeff[RED][3] += lambda * Y3(dir);
						shCoeff[RED][4] += lambda * Y4(dir);
						shCoeff[RED][5] += lambda * Y5(dir);
						shCoeff[RED][6] += lambda * Y6(dir);
						shCoeff[RED][7] += lambda * Y7(dir);
						shCoeff[RED][8] += lambda * Y8(dir);

						lambda = (pixels[GREEN] * dColor) * solidAngle;
						shCoeff[GREEN][0] += lambda * Y0(dir);
						shCoeff[GREEN][1] += lambda * Y1(dir);
						shCoeff[GREEN][2] += lambda * Y2(dir);
						shCoeff[GREEN][3] += lambda * Y3(dir);
						shCoeff[GREEN][4] += lambda * Y4(dir);
						shCoeff[GREEN][5] += lambda * Y5(dir);
						shCoeff[GREEN][6] += lambda * Y6(dir);
						shCoeff[GREEN][7] += lambda * Y7(dir);
						shCoeff[GREEN][8] += lambda * Y8(dir);

						lambda = (pixels[BLUE] * dColor) * solidAngle;
						shCoeff[BLUE][0] += lambda * Y0(dir);
						shCoeff[BLUE][1] += lambda * Y1(dir);
						shCoeff[BLUE][2] += lambda * Y2(dir);
						shCoeff[BLUE][3] += lambda * Y3(dir);
						shCoeff[BLUE][4] += lambda * Y4(dir);
						shCoeff[BLUE][5] += lambda * Y5(dir);
						shCoeff[BLUE][6] += lambda * Y6(dir);
						shCoeff[BLUE][7] += lambda * Y7(dir);
						shCoeff[BLUE][8] += lambda * Y8(dir);

						pixels += nc;
					}
				}

				const float domega = 2.0f * 3.14f / sumWeight;
				for (int i = 0; i < 9; ++i)
				{
					shCoeff[RED][i] *= domega;
					shCoeff[GREEN][i] *= domega;
					shCoeff[BLUE][i] *= domega;
				}

				const float c1 = 0.429043f;
				const float c2 = 0.511664f;
				const float c3 = 0.743125f;
				const float c4 = 0.886227f;
				const float c5 = 0.247708f;

				glm::mat4 M[3];

				for (int c = 0; c < 3; ++c)
				{
					M[c][0][0] = c1 * shCoeff[c][8];
					M[c][0][1] = c1 * shCoeff[c][4];
					M[c][0][2] = c1 * shCoeff[c][7];
					M[c][0][3] = c2 * shCoeff[c][3];

					M[c][1][0] = c1 * shCoeff[c][4];
					M[c][1][1] = -c1 * shCoeff[c][8];
					M[c][1][2] = c1 * shCoeff[c][5];
					M[c][1][3] = c2 * shCoeff[c][1];

					M[c][2][0] = c1 * shCoeff[c][7];
					M[c][2][1] = c1 * shCoeff[c][5];
					M[c][2][2] = c3 * shCoeff[c][6];
					M[c][2][3] = c2 * shCoeff[c][2];

					M[c][3][0] = c2 * shCoeff[c][3];
					M[c][3][1] = c2 * shCoeff[c][1];
					M[c][3][2] = c2 * shCoeff[c][2];
					M[c][3][3] = c4 * shCoeff[c][0] - c5 * shCoeff[c][6];
				}

				auto rg = gSys->pEngine->pRenderer->GetRadianceGen();
				rg->shValues_r = M[0];
				rg->shValues_g = M[1];
				rg->shValues_b = M[2];
				gSys->Log("Generated face sh", nullptr);
			}

			Sleep(10000);

		}
	}
	return 0;
}

void CRadianceGen::Render()
{
	Vec3 pos = Vec3(0, 30.f, 0);
	glm::mat4 views[6] = {
		glm::lookAt(pos, pos+glm::vec3(1,0,0),glm::vec3(0,-1,0)),
		glm::lookAt(pos, pos+glm::vec3(-1,0,0),glm::vec3(0,-1,0)),
		glm::lookAt(pos, pos+glm::vec3(0,1,0),glm::vec3(0,0,1)),
		glm::lookAt(pos, pos+glm::vec3(0,-1,0),glm::vec3(0,0,-1)),
		glm::lookAt(pos, pos+glm::vec3(0,0,1),glm::vec3(0,-1,0)),
		glm::lookAt(pos, pos+glm::vec3(0,0,-1),glm::vec3(0,-1,0))
	};
	glm::mat4 p = glm::perspective(90.f, (float)m_pGBuffer->width / (float)m_pGBuffer->height, 0.1f, 1000.0f);
	for (int i = 0; i < 6; i++)
	{
		m_pGBuffer->Begin();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		m_pGBuffer->MeshPass();

		for (std::pair<unsigned int, IMesh*> it : gSys->pEngine->pMeshSystem->GetMeshContainer())
		{
			IMesh* pMesh = it.second;
			glBindVertexArray(pMesh->GetVertexArray());
			glUseProgram(pMesh->GetShader()->GetProgramId());

			glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[MODELMAT], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));
			glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[VIEWMAT], 1, GL_FALSE, glm::value_ptr(views[i]));
			glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[PROJMAT], 1, GL_FALSE, glm::value_ptr(p));
			glUniformMatrix4fv(pMesh->GetShader()->GetUniforms()[OBJ2WORLD], 1, GL_FALSE, glm::value_ptr(pMesh->GetModelMatrix()));

			if (pMesh->GetTexture() != nullptr)
				pMesh->GetTexture()->ActivateTexture(GL_TEXTURE10, pMesh->GetShader()->GetUniforms()[TEXTURESAMPLER]);

			glDrawElements(GL_TRIANGLES, pMesh->GetIndexCount() * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
		}
		gSys->pEngine->pRenderer->GetSkybox()->Draw();
		m_pGBuffer->RenderQuad();
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, m_pGBuffer->width, m_pGBuffer->height, GL_RGB, GL_UNSIGNED_BYTE, data[i]);
	}
	souldGenerate = true;
}

void CRadianceGen::GetTexelAttrib(const int texId, const float u, const float v, const float texelSize,
	glm::vec3 *direction, float *solidAngle)
{
	enum
	{
		POSITIVE_X, NEGATIVE_X,
		POSITIVE_Y, NEGATIVE_Y,
		POSITIVE_Z, NEGATIVE_Z
	};


	// Compute the texel direction  
	switch (texId)
	{
	case POSITIVE_X:
		*direction = glm::vec3(+1.0f, -v, -u);
		break;

	case NEGATIVE_X:
		*direction = glm::vec3(-1.0f, -v, +u);
		break;

	case POSITIVE_Y:
		*direction = glm::vec3(+u, +1.0f, +v);
		break;

	case NEGATIVE_Y:
		*direction = glm::vec3(+u, -1.0f, -v);
		break;

	case POSITIVE_Z:
		*direction = glm::vec3(+u, -v, +1.0f);
		break;

	case NEGATIVE_Z:
		*direction = glm::vec3(-u, -v, -1.0f);
		break;
	}

	*direction = glm::normalize(*direction);

	float x0 = u - texelSize;
	float y0 = v - texelSize;
	float x1 = u + texelSize;
	float y1 = v + texelSize;

#define AREA(x, y)  atan2f(x * y, sqrtf(x * x + y * y + 1.0))
	*solidAngle = (AREA(x0, y0) + AREA(x1, y1)) - (AREA(x0, y1) + AREA(x1, y0));
#undef AREA  
}

CRadianceGen::CRadianceGen()
{
	souldGenerate = false;
	m_shThread = CreateThread(nullptr, 0, ShThread, 0, 0, nullptr);
	m_pGBuffer = new CGBuffer(64, 64, "data/radiance_final.fx");
}

CRadianceGen::~CRadianceGen()
{
	TerminateThread(m_shThread, 0);
	delete m_pGBuffer;
}
