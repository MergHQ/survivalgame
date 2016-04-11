#pragma once
#include "ILight.h"

class CEnvironmentProbe : public ILight
{
public:
	CEnvironmentProbe();
	~CEnvironmentProbe();

	// ILight
	virtual glm::vec3& GetLightPosition() { return m_pos; };
	virtual void SetLightPosition(glm::vec3& pos) { m_pos = pos; };
	virtual glm::vec3& GetSetLightColor(glm::vec3 color, bool set) { return glm::vec3(); };
	virtual CShadowGen* GetShadowMap() { return nullptr; }
	// ~ILight

	// Create new textures.
	void Update();

	// Environment probe values.
	BYTE data[6][64 * 64 * 3];
	glm::mat4x4 shValues_r;
	glm::mat4x4 shValues_g;
	glm::mat4x4 shValues_b;

private:
	glm::vec3 m_pos;
};

