#pragma once
#include "GBuffer.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void InitDependencies();
	void Render();

private:
	void MeshPass();
	void ClearFrame();
	CGBuffer* m_pGBuffer;
};

