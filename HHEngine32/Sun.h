#pragma once
#include "ILight.h"

class __declspec(dllexport) CSun : public ILight
{
public:
	CSun();
	~CSun();

	// ILight
	virtual glm::vec3& GetLightPosition() { return m_pos; }
	virtual void SetLightPosition(glm::vec3& pos) { m_pos = pos; }
	virtual glm::vec3& GetSetLightColor(glm::vec3 color, bool set);
	virtual CShadowGen* GetShadowMap() { return m_pShadowGen; }
	// ~~ILight
	void Update();

	bool castShadows;

private:
	glm::vec3 m_pos;
	glm::vec3 m_color;
	float m_angle;
	CShadowGen* m_pShadowGen;
};

