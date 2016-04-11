#include "stdafx.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include "Input.h"
#include "Game.h"
#include <Engine.h>
#include "CameraSystem.h"
#include "TerrainGen.h"

CCamera::CCamera()
{
	m_cameraPos = Vec3(0, 1.8f, 0);
	// Projection matrix : FOV = 45, aspect ratio, near plane, far plane
	m_pmatrix = glm::perspective(45.f, (float)p_gSys->pEngine->pCamSys->GetWinStats()[0] / (float)p_gSys->pEngine->pCamSys->GetWinStats()[1], 0.1f, 1000.0f);

	p_gSys->pEngine->pInput->addListener(this);
	p_gSys->pEngine->pCamSys->RegisterCamera(this);
}

CCamera::~CCamera()
{
}

void CCamera::Update(GLFWwindow* w, double dt)
{
	// Looking around
	double xpos, ypos;
	xpos = p_gSys->pEngine->pCamSys->GetMousePos()[0];
	ypos = p_gSys->pEngine->pCamSys->GetMousePos()[1];

	m_horizontalAngle += m_sensitivity * (m_oldx - xpos);
	m_verticalAngle += m_sensitivity * (m_oldy - ypos);

	m_oldx = xpos;
	m_oldy = ypos;

	m_direction = Vec3(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
		);


	// Movement
	if (m_forward != m_backwards || m_right != m_left)
		move(w, dt);

	if(p_gSys->pGame)
		m_cameraPos.y = p_gSys->pGame->pTerrainGen->GetTerrainHeight((int)m_cameraPos.x, (int)m_cameraPos.z)+1.8f;

	// Construct View Matrix
	m_vmatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_direction, Vec3(0, 1, 0));
}

bool CCamera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		m_speed = 0.5f;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
	{
		m_speed = 0.1f;
	}

	CCameraSystem* pCs = p_gSys->pEngine->pCamSys;

	bool move =
		pCs->GetKeyState(GLFW_KEY_W) == GLFW_PRESS ||
		pCs->GetKeyState(GLFW_KEY_A) == GLFW_PRESS ||
		pCs->GetKeyState(GLFW_KEY_S) == GLFW_PRESS ||
		pCs->GetKeyState(GLFW_KEY_D) == GLFW_PRESS;

	setMovement(
		pCs->GetKeyState(GLFW_KEY_W) == GLFW_PRESS, pCs->GetKeyState(GLFW_KEY_S) == GLFW_PRESS,
		pCs->GetKeyState(GLFW_KEY_D) == GLFW_PRESS, pCs->GetKeyState(GLFW_KEY_A) == GLFW_PRESS
		);
	return move;
}


void CCamera::setMovement(bool forward, bool backwards, bool right, bool left)
{
	m_forward = forward;
	m_backwards = backwards;
	m_right = right;
	m_left = left;
}

void CCamera::move(GLFWwindow *window, float delta)
{
	Vec3 right = Vec3(
		sin(m_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_horizontalAngle - 3.14f / 2.0f)
		);

	Vec3 up = glm::cross(right, m_direction);

	// Forward on ground
	Vec3 forwardDir = Vec3(
		m_direction.x,
		0,
		m_direction.z
		);

	// Right on ground
	Vec3 rightDir = Vec3(
		-forwardDir.z,
		0,
		forwardDir.x
		);

	bool editor = true;

	if (m_forward)
	{
		m_cameraPos += (editor ? m_direction : forwardDir) * delta * m_speed;
	}
	if (m_backwards)
	{
		m_cameraPos -= (editor ? m_direction : forwardDir) * delta * m_speed;
	}

	if (m_right)
	{
		m_cameraPos += (editor ? right : rightDir) * delta * m_speed;
	}
	if (m_left)
	{
		m_cameraPos -= (editor ? right : rightDir) * delta * m_speed;
	}
}
