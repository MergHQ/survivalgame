#include "main.h"
#include <Windows.h>
#include <GlobalSystem.h>

int main()
{
	CMainWindow();
	return 0;
}

extern "C" __declspec(dllimport) void EngineMain(SGlobalSystem* pSys);

void CMainWindow::Init()
{
	HINSTANCE engineDll = NULL;
	// Load engine module
	engineDll = LoadLibraryW(L"HHEngine32.dll");
	if (engineDll != NULL)
		EngineMain(nullptr);
	FreeLibrary(engineDll);

}
