#pragma once
#include "Sun.h"
#include "ILight.h"
#include "IMesh.h"
#include "IShader.h"
#include <vector>

class CSun;

class __declspec(dllexport) CLightSystem
{
public:
	CLightSystem();
	~CLightSystem();

	ILight* CreatePointLight(glm::vec3 pos, glm::vec3 color);
	void DrawLights();
	ILight* GetSun() { return m_pSun; }
private:
	std::vector<ILight*> m_lights;
	CSun* m_pSun;
	IShader* m_pNullShader;
	IMesh* lightSphere;
};

