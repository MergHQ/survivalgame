#include "stdafx.h"
#include "GlobalSystem.h"
#include <iostream>
#include "Engine.h"
#include <GLFW\glfw3.h>
#include <Game.h>

extern "C" __declspec(dllimport) void GameMain(SGlobalSystem* gSys, CGame* pGame);

SGlobalSystem::SGlobalSystem(GLFWwindow* win)
{
	pWin = win;
	pGame = nullptr;
}

SGlobalSystem::~SGlobalSystem()
{
	delete pGame;
	FreeLibrary(m_gameModule);
	delete pEngine;
}

void SGlobalSystem::Init()
{
	pEngine = new CEngine;
	pEngine->Init();
	gSys->Log("HHEngine32 loaded (32-bit OpenGL)", this);


	// Load game module
	m_gameModule = LoadLibraryW(L"GameModule.dll");
	if (m_gameModule != NULL)
	{
		GameMain(this, pGame);
		Log("Game module loaded", this);
	}
}

void SGlobalSystem::Update()
{
	pEngine->Update();
}