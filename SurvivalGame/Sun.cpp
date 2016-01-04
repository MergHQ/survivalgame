#include "Sun.h"

CSun::CSun()
{
	m_color = glm::vec3(1,0.5,0);
	m_pos = glm::vec3(2000, 1500, 2000);
}

CSun::~CSun()
{
}

glm::vec3& CSun::GetSetLightColor(glm::vec3 color, bool set)
{
	if (set)
		m_color = color;
	return m_color;
}

