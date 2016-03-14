#include "main.h"
#include <Windows.h>
#include <GlobalSystem.h>

int main()
{
	CMainWindow();
	return 0;
}

extern "C" __declspec(dllimport) void EngineMain(SGlobalSystem* pSys);
SGlobalSystem*  _gSys;
void CMainWindow::Init()
{
	HINSTANCE engineDll = NULL;
	// Load engine module
	engineDll = LoadLibraryW(L"HHEngine32.dll");
	if (engineDll != NULL)
		EngineMain(_gSys);
	while (true) 
	{
		if (_gSys != nullptr)
			_gSys->Log("Sjit", nullptr);
	};
	FreeLibrary(engineDll);

}
