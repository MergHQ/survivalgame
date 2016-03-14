#include "stdafx.h"
#include "FboTexture.h"

CFboTexture::CFboTexture(GLint cbt, GLint dataType, GLint colorAttachment, int width, int height)
{
	int mode;

	if (cbt == GL_RGB32F)
		mode = GL_RGB;
	else if (cbt == GL_RGBA32F)
		mode = GL_RGBA;
	else if (cbt == GL_RGBA16F)
		mode = GL_RGB;
	else if (cbt == GL_DEPTH32F_STENCIL8)
		mode = GL_DEPTH_STENCIL;
	else if (cbt == GL_RGBA)
		mode = GL_RGB;
	else mode = cbt;

	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glTexImage2D(GL_TEXTURE_2D, 0, cbt, width, height, 0, mode, dataType, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, colorAttachment, m_texId, 0);
}

CFboTexture::~CFboTexture()
{
	glDeleteTextures(1, &m_texId);
}

void CFboTexture::ActivateTexture(GLuint activate, GLuint uniformLoc)
{
	glActiveTexture(activate);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	int offset = activate - 0x84C0;
	glUniform1i(uniformLoc, offset);
}
