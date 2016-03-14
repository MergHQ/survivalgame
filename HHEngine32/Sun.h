#pragma once
#include "ILight.h"

class CSun : public ILight
{
public:
	CSun();
	~CSun();

	// ILight
	virtual glm::vec3& GetLightPosition() { return m_pos; }
	virtual void SetLightPosition(glm::vec3& pos) { m_pos = pos; }
	virtual glm::vec3& GetSetLightColor(glm::vec3 color, bool set);
	// ~~ILight
	bool castShadows;

private:
	glm::vec3 m_pos;
	glm::vec3 m_color;
};

