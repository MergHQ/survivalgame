#include "Game.h"
#include "Camera.h"
#include "TerrainGen.h"

CGame::CGame()
{
}

CGame::~CGame()
{
	delete pCamera;
	delete pTerrainGen;
}

void CGame::Init()
{
	pCamera = new CCamera;

	pTerrainGen = new CTerrainGen;
	pTerrainGen->GenerateTerrain(1024, 1024, 2.0, 20.0, 1.0, 30.0);
}

void CGame::Update()
{
	pCamera->Update(1.0, gSys->pWin);
}
