#pragma once

#include "IInputListener.h"
#include "GlobalSystem.h"
#include <GLFW\glfw3.h>
#include <glm\mat4x4.hpp>
#include "ICamera.h"

enum CameraMode
{
	EDITOR, GAME
};

class CCamera : public IInputListener, public ICamera
{
public:
	CCamera();
	~CCamera();

	virtual void Update(GLFWwindow* w, double dt);
	virtual glm::vec3& GetPosition() { return m_cameraPos; };
	virtual glm::mat4& GetViewMatrix() { return m_vmatrix; };
	virtual glm::mat4& GetProjectionMatrix() { return m_pmatrix; };

	//IInputListener
	virtual bool key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//~IInputListener

	void move(GLFWwindow *window, float delta);
protected:
	void setMovement(bool forward, bool backwards, bool right, bool left);
private:
	bool m_forward = false, m_backwards = false, m_right = false, m_left = false;
	double m_horizontalAngle = 0, m_verticalAngle = 0;
	double xpos, ypos;
	double m_oldx = 0, m_oldy = 0;
	float m_speed = 0.0833f; //5m/s if one unit is a meter.
	float m_sensitivity = 0.001f;
	int m_currentCameraMode;
	int width, height;
	Vec3 m_direction;
	Vec3 m_cameraPos;
	glm::mat4 m_vmatrix;
	glm::mat4 m_pmatrix;
};
