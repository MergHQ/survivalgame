#include "stdafx.h"
#include "PointLight.h"

CPointLight::CPointLight(glm::vec3 pos, glm::vec3 color)
{
	m_pos = pos;
	m_color = color;
	m_attenuation = glm::vec3(1, 1, 1);

	radius = CalcRadius();
}

CPointLight::~CPointLight()
{
}

glm::vec3& CPointLight::GetSetLightColor(glm::vec3 color, bool set)
{
	if (set)
		m_color = color;

	return m_color;
}

float CPointLight::CalcRadius()
{
	float MaxChannel = fmax(fmax(m_color.x, m_color.y), m_color.z);

	float ret = (-m_attenuation.x + sqrtf(m_attenuation.x * m_attenuation.x -
		4 * m_attenuation.y * (m_attenuation.y - 256 * MaxChannel * m_attenuation.z)))
		/
		2 * m_attenuation.y;
	return ret;
}
