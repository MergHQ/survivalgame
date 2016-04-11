#include "stdafx.h"
#include "Sun.h"
#include <glm\gtc\matrix_transform.hpp>

CSun::CSun()
{
	m_angle = 0;
	m_color = glm::vec3(1,1,1);
	m_pos = glm::vec3(2000, 1500, 2000);
	m_pShadowGen = new CShadowGen(2048, 2048, glm::ortho<float>(-20, 20, -20, 20, -20, 200));
}

CSun::~CSun()
{
	delete m_pShadowGen;
}

glm::vec3& CSun::GetSetLightColor(glm::vec3 color, bool set)
{
	if (set)
		m_color = color;
	return m_color;
}

void CSun::Update()
{
	m_angle += 0.01;
	m_pos = glm::vec3(2000, 1500, 2000);
	m_pShadowGen->ShadowPass(m_pos/100.f);

}

