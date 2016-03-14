#pragma once

class CMeshSystem;
class CRenderer;
class CInput;
class CCameraSystem;

class CEngine
{
public:
	CEngine();
	~CEngine();

	CRenderer* pRenderer;
	CMeshSystem* pMeshSystem;
	CInput* pInput;
	CCameraSystem* pCamSys;

	void Init();
	void Update();
};

