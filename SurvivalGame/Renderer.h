#pragma once
#include "GBuffer.h"
#include "IShader.h"
#include "LightSystem.h"

class CSSAO;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void InitDependencies();
	void Render();
	CSSAO* GetSSAOProcessor() { return m_pSSAO; }
	CLightSystem* GetLightSystem() { return m_pLightSystem; }
	CGBuffer* GetGBuffer() { return m_pGBuffer; }

private:
	void MeshPass();
	void ClearFrame();
	CGBuffer* m_pGBuffer;
	CSSAO* m_pSSAO;
	CLightSystem* m_pLightSystem;
};

