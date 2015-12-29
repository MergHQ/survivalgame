#pragma once

class CMeshSystem;
class CRenderer;

class CEngine
{
public:
	CEngine();
	~CEngine();

	CRenderer* pRenderer;
	CMeshSystem* pMeshSystem;

	void Init();
	void Update();
};

