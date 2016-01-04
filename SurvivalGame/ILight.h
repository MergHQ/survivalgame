#pragma once
#include <glm\common.hpp>

struct ILight
{
	virtual glm::vec3& GetLightPosition() = 0;
	virtual void SetLightPosition(glm::vec3& pos) = 0;
	virtual glm::vec3& GetSetLightColor(glm::vec3 color, bool set) = 0;
};