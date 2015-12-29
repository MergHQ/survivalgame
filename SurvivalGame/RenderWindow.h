#pragma once
#include <GLFW\glfw3.h>

class CRenderWindow
{
public:
	CRenderWindow();
	~CRenderWindow();

	void Create(int x, int y);
	GLFWwindow* GetWindow() { return m_pWin; }
private:
	GLFWwindow* m_pWin;
};

