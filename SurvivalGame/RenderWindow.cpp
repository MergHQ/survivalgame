#include "RenderWindow.h"
#include <stdlib.h>
#include <stdio.h>
#include "Engine.h"
#include "Input.h"
#include "Renderer.h"

SGlobalSystem* gSys;

CRenderWindow::CRenderWindow()
{
}


CRenderWindow::~CRenderWindow()
{
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	gSys->pEngine->pInput->key_callback(window, key, scancode, action, mods);
}

void CRenderWindow::Create(int x, int y, SGlobalSystem* sys)
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
	glfwSetKeyCallback(m_pWin, key_callback);
	glfwSetInputMode(m_pWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewInit();

	sys = new SGlobalSystem(m_pWin);
	gSys = sys;
	sys->Init();

	while (!glfwWindowShouldClose(m_pWin))
	{
		//Update
		sys->Update();

		glfwSwapBuffers(m_pWin);
		glfwPollEvents();
	}

	glfwDestroyWindow(m_pWin);
	glfwTerminate();
}
