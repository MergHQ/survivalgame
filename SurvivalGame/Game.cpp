#include "Game.h"
#include "Camera.h"

CGame::CGame()
{
}

CGame::~CGame()
{
	delete pCamera;
}

void CGame::Init()
{
	pCamera = new CCamera;
}

void CGame::Update()
{
	pCamera->Update(1.0, gSys->pWin);
}
