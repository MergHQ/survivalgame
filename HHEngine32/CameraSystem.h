#pragma once
#include <map>
#include "ICamera.h"

class CCameraSystem
{
public:
	CCameraSystem();
	~CCameraSystem();

	// Register and use as primary camera.
	void RegisterCamera(ICamera* pCam);
	void Update();
	void Use(ICamera* pCam);
	ICamera* GetCurrentCamera();

private:
	std::map<bool,ICamera*> m_cameras;
};

