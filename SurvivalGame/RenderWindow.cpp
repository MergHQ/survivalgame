#include "RenderWindow.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "GlobalSystem.h"

CRenderWindow::CRenderWindow()
{
}


CRenderWindow::~CRenderWindow()
{
}

void CRenderWindow::Create(int x, int y)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	m_pWin = glfwCreateWindow(x, y, "Game", NULL, NULL);
	if (!m_pWin)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_pWin);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(m_pWin))
	{
		//Update
		gSys->Update();
		gSys->Log("asd", this);

		glfwSwapBuffers(m_pWin);
		glfwPollEvents();
	}

	glfwDestroyWindow(m_pWin);
	glfwTerminate();
}
