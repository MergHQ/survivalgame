#include "stdafx.h"
#include "RenderWindow.h"
#include "main.h"

extern "C" __declspec(dllexport) void EngineMain(SGlobalSystem* sys)
{
	auto win = new CRenderWindow;
	sys = gSys;
	win->Create(1280, 720, gSys);
	delete win;
	delete gSys;
}