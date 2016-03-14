#include "stdafx.h"
#include "GlobalSystem.h"
#include <iostream>
#include "Engine.h"
#include <GLFW\glfw3.h>
#include <Windows.h>

SGlobalSystem::SGlobalSystem(GLFWwindow* win)
{
	pWin = win;
}

SGlobalSystem::~SGlobalSystem()
{
	delete pEngine;
}

void SGlobalSystem::Init()
{
	pEngine = new CEngine;
	pEngine->Init();
	gSys->Log("HHEngine32 loaded (32-bit OpenGL)", this);
}

void SGlobalSystem::Update()
{
	pEngine->Update();
}