#pragma once

class CCamera;
class CTerrainGen;

class CGame
{
public:
	CGame();
	~CGame();

	CCamera* pCamera;
	CTerrainGen* pTerrainGen;

	void Init();
	void Update();
};

