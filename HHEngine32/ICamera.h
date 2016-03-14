#pragma once
#include <glm\vec3.hpp>
#include <glm\common.hpp>

struct GLFWwindow;

struct ICamera
{
	virtual ~ICamera() {};
	virtual void Update(GLFWwindow* w, double dt) = 0;
	virtual glm::vec3& GetPosition() = 0;
	virtual glm::mat4& GetViewMatrix() = 0;
	virtual glm::mat4& GetProjectionMatrix() = 0;
};