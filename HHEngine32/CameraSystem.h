#pragma once
#include <vector>
#include <map>
#include "ICamera.h"

class __declspec(dllexport) CCameraSystem
{
public:
	CCameraSystem();
	~CCameraSystem();

	// Register and use as primary camera.
	void RegisterCamera(ICamera* pCam);
	void Update();
	void Use(ICamera* pCam);
	ICamera* GetCurrentCamera();

	// Wrappers for cross-dll.
	// GLFW functions can only be used on the main thread.
	std::vector<int> GetWinStats();
	std::vector<double> GetMousePos();
	UINT GetKeyState(UINT key);
	//

private:
	std::map<bool,ICamera*> m_cameras;
};

