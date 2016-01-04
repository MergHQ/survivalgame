#include "Texture.h"
#include "lodepng.h"
#include "GlobalSystem.h"

CTexture::CTexture(std::string file)
{
	unsigned int width, height;
	std::vector<unsigned char> image;

	auto e = lodepng::decode(image, width, height, file.c_str());

	if (e != 0)
	{
		gSys->Log("Could not load texture: " + file, this);
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

CTexture::~CTexture()
{
	glDeleteTextures(1, &m_texId);
}

void CTexture::ActivateTexture(GLuint activate, GLuint uniformLoc)
{
	glActiveTexture(activate);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	int offset = activate - 0x84C0;
	glUniform1i(uniformLoc, offset);
}
