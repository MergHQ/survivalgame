#pragma once
#include "ITexture.h"

class CFboTexture : public ITexture
{
public:
	CFboTexture(GLint cbt, GLint dataType, GLint colorAttachment, int width, int height);
	~CFboTexture();

	// ITexture
	virtual void ActivateTexture(GLuint activate, GLuint uniformLoc);
	virtual GLuint& GetTextureId() { return m_texId; }
	virtual std::string GetFileName() { return m_fileName; }
	// ~ITexture
public:
	std::string m_fileName;
	GLuint m_texId;
};

