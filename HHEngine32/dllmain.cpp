// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Engine.h"
#include "RenderWindow.h"
#include "GlobalSystem.h"

HMODULE g_hModule;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			g_hModule = hModule;

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}

	return TRUE;
}
