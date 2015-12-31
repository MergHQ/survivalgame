#include "GBuffer.h"
#include "GlobalSystem.h"
#include "Engine.h"
#include "FboTexture.h"
#include "Shader.h"

CGBuffer::CGBuffer()
{

	m_pQuadShader = new CShader("data/final.fx");

	glfwGetFramebufferSize(gSys->pWin, &width, &height);

	m_frameBuffer = 0;
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	
	m_textures.push_back(new CFboTexture(GL_RGBA, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0, width, height));
	m_textures.push_back(new CFboTexture(GL_RGB32F, GL_FLOAT, GL_COLOR_ATTACHMENT1, width, height));
	m_textures.push_back(new CFboTexture(GL_RGB32F, GL_FLOAT, GL_COLOR_ATTACHMENT2, width, height));
	m_textures.push_back(new CFboTexture(GL_DEPTH32F_STENCIL8, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, GL_DEPTH_STENCIL_ATTACHMENT, width, height));

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		gSys->Log("Failed creating framebuffer.",this);
	}

	CreateQuad();
}


void CGBuffer::CreateQuad()
{
	const GLfloat QuadVerts[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	std::vector<uint32_t> QuadIndices =
	{
		2, 0, 1, 2, 1, 3
	};

	GLuint vbo, ibo;

	m_quadVao = 0;
	glGenVertexArrays(1, &m_quadVao);
	glBindVertexArray(m_quadVao);

	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sizeof(QuadVerts), &QuadVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_FALSE, (GLubyte *)NULL);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, QuadIndices.size() * sizeof(uint32_t), &QuadIndices[0], GL_STATIC_DRAW);
	m_indices = QuadIndices.size();
	 
	glBindVertexArray(NULL);
}


CGBuffer::~CGBuffer()
{
	glDeleteFramebuffers(1, &m_frameBuffer);

	for (ITexture* t : m_textures)
		delete t;

	delete m_pQuadShader;
}

void CGBuffer::RenderQuad()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_pQuadShader->GetProgramId());

	for (int i = 0; i < m_textures.size(); i++)
		m_textures[i]->ActivateTexture(0x84C0 + i, m_pQuadShader->GetUniforms()[gCOLOR + i]);

	glUniform1i(m_pQuadShader->GetUniforms()[WIDTH], width);
	glUniform1i(m_pQuadShader->GetUniforms()[HEIGHT], height);
	glBindVertexArray(m_quadVao);
	glDrawElements(GL_TRIANGLES, m_indices * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}

void CGBuffer::MeshPass()
{
	GLenum DrawBuffers[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, DrawBuffers);
}

void CGBuffer::Begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glViewport(0, 0, width, height);
}
