#include "GlobalSystem.h"
#include <iostream>
#include "Game.h"
#include "Engine.h"
#include <GLFW\glfw3.h>

SGlobalSystem::SGlobalSystem(GLFWwindow* win)
{
	pWin = win;
}

SGlobalSystem::~SGlobalSystem()
{
	delete pGame;
	delete pEngine;
}

void SGlobalSystem::Init()
{
	pEngine = new CEngine;
	pEngine->Init();

	pGame = new CGame;
	pGame->Init();
}

void SGlobalSystem::Update()
{
	pEngine->Update();
	pGame->Update();
}