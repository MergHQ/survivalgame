#pragma once
#include "IShader.h"
#include "ITexture.h"
#include <vector>

class CGBuffer
{
public:
	CGBuffer();
	~CGBuffer();

	void RenderQuad();
	std::vector<ITexture*>& GetTextures() { return m_textures; }
	void MeshPass();
	void Begin();

	int width, height;
private:
	IShader* m_pQuadShader;
	void CreateQuad();
	GLuint m_frameBuffer, m_quadVao;
	size_t m_indices;
	std::vector<ITexture*> m_textures;
};

