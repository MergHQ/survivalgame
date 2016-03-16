#include "stdafx.h"
#include "Game.h"
#include "TerrainGen.h"
#include "Camera.h"
#include <GlobalSystem.h>

SGlobalSystem* p_gSys;

CGame::CGame()
{
}

CGame::~CGame()
{
	delete pTerrainGen;
	delete pCamera;
}

void CGame::Init()
{
	p_gSys->pGame = this;
	pCamera = new CCamera;

	pTerrainGen = new CTerrainGen;
	pTerrainGen->GenerateTerrain(1024, 1024, 2.0, 20.0, 1.0, 10.0);
}