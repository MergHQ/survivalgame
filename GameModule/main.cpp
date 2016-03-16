#include "stdafx.h"
#include "Game.h"

extern "C" __declspec(dllexport) void GameMain(SGlobalSystem* gSys, CGame* pGame)
{
	CGame* game = new CGame;
	p_gSys = gSys;
	game->Init();
}