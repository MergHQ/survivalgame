#include "stdafx.h"
#include "CameraSystem.h"
#include <algorithm>
#include "GlobalSystem.h"
#include "Engine.h"
#include <GLFW\glfw3.h>

CCameraSystem::CCameraSystem()
{
}

CCameraSystem::~CCameraSystem()
{
	for (std::pair<bool, ICamera*> o : m_cameras)
		delete o.second;
}

void CCameraSystem::RegisterCamera(ICamera* pCam)
{
	m_cameras[true] = pCam;
}

void CCameraSystem::Update()
{
	for (std::pair<bool, ICamera*> o : m_cameras) 
		o.second->Update(gSys->pWin, 1.0);
}

void CCameraSystem::Use(ICamera* pCam)
{
	// TODO: Implement
	return;
}

ICamera* CCameraSystem::GetCurrentCamera()
{
	for (std::pair<bool, ICamera*> o : m_cameras)
		if (o.first)
			return o.second;
}

std::vector<int> CCameraSystem::GetWinStats()
{
	std::vector<int> res;
	int h, w;
	glfwGetFramebufferSize(gSys->pWin, &w, &h);
	res.push_back(w);
	res.push_back(h);
	return res;
}

std::vector<double> CCameraSystem::GetMousePos()
{
	std::vector<double> res;
	double x, y;
	glfwGetCursorPos(gSys->pWin, &x, &y);
	res.push_back(x);
	res.push_back(y);
	return res;
}

UINT CCameraSystem::GetKeyState(UINT key)
{
	return glfwGetKey(gSys->pWin, key);
}
