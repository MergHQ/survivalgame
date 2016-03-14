#include "stdafx.h"
#include "CameraSystem.h"
#include <algorithm>
#include "GlobalSystem.h"
#include "Engine.h"

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
