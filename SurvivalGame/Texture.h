#pragma once
#include "ITexture.h"

class CTexture : public ITexture
{
public:

	CTexture(std::string file);
	~CTexture();

	// ITexture
	virtual void ActivateTexture(GLuint activate, GLuint uniformLoc);
	virtual GLuint& GetTextureId() { return m_texId; }
	virtual std::string GetFileName() { return m_texFile; }
	// ~ITexture

private:
	std::string m_texFile;
	GLuint m_texId;

};

