#include "main.h"
#include "GlobalSystem.h"
#include "RenderWindow.h"

SGlobalSystem* gSys;

int main()
{
	CMainWindow();
	return 0;
}

void CMainWindow::Init()
{
	gSys = new SGlobalSystem;
	gSys->Init();

	CRenderWindow* pWin = new CRenderWindow;
	pWin->Create(1280, 720);
	delete pWin;
	delete gSys;
	exit(EXIT_SUCCESS);
}
