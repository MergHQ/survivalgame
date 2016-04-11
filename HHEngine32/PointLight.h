#pragma once
#include "ILight.h"

class CPointLight : public ILight
{
public:
	CPointLight(glm::vec3 pos, glm::vec3 color);
	~CPointLight();

	// ILight
	virtual glm::vec3& GetLightPosition() { return m_pos; }
	virtual void SetLightPosition(glm::vec3& pos) { m_pos = pos; }
	virtual glm::vec3& GetSetLightColor(glm::vec3 color, bool set);
	virtual CShadowGen* GetShadowMap() { return nullptr; } // TODO: implement omnidirectional shadowmaps.
	// ~~ILight

	float CalcRadius();
	glm::vec3& GetAttenuation() { return m_attenuation; }
	bool castShadows;
	float radius = 0.0f;
private:
	glm::vec3 m_pos;
	glm::vec3 m_color;
	glm::vec3 m_attenuation;
};

