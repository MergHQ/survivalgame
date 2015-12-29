#pragma once

class CMeshSystem;
class CRenderer;
class CInput;

class CEngine
{
public:
	CEngine();
	~CEngine();

	CRenderer* pRenderer;
	CMeshSystem* pMeshSystem;
	CInput* pInput;

	void Init();
	void Update();
};

