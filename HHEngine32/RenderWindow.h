#pragma once
#include <GL\glew.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>
#include "GlobalSystem.h"

class CRenderWindow
{
public:
	CRenderWindow();
	~CRenderWindow();

	void Create(int x, int y, SGlobalSystem* sys);
	GLFWwindow* GetWindow() { return m_pWin; }
private:
	GLFWwindow* m_pWin;
};

