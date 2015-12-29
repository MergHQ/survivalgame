#include "GlobalSystem.h"
#include <iostream>
#include "Game.h"
#include "Engine.h"

SGlobalSystem::~SGlobalSystem()
{
	delete pGame;
	delete pEngine;
}

void SGlobalSystem::Init()
{
	pGame = new CGame;
	pGame->Init();

	pEngine = new CEngine;
	pEngine->Init();
}

void SGlobalSystem::Update()
{
	pEngine->Update();
	pGame->Update();
}