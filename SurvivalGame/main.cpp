#include "main.h"
#include "GlobalSystem.h"
#include "RenderWindow.h"

int main()
{
	CMainWindow();
	return 0;
}

void CMainWindow::Init()
{
	CRenderWindow* pWin = new CRenderWindow;
	pWin->Create(1920, 1080, gSys);

	delete pWin;
	delete gSys;
	exit(EXIT_SUCCESS);
}
