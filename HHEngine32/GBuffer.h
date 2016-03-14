#pragma once
#include "IShader.h"
#include "ITexture.h"
#include <vector>

class CGBuffer
{
public:
	CGBuffer(int w = 0, int h = 0, std::string shader = "data/final.fx");
	~CGBuffer();

	void RenderQuad();
	std::vector<ITexture*>& GetTextures() { return m_textures; }
	IShader* GetShader() { return m_pQuadShader; }
	void MeshPass();
	void StencilPass();
	void LightPass();
	void Begin();

	int width, height;
private:
	IShader* m_pQuadShader;
	void CreateQuad();
	GLuint m_frameBuffer, m_quadVao;
	size_t m_indices;
	std::vector<ITexture*> m_textures;
};

