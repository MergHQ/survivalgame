#pragma once

class CCamera;
class CTerrainGen;
struct SGlobalSystem;
class CCamera;

class __declspec(dllexport) CGame
{
public:
	CGame();
	~CGame();

	void Init();
	CCamera* pCamera;
	CTerrainGen* pTerrainGen;
};

extern SGlobalSystem* p_gSys;

