#pragma once

class CCamera;

class CGame
{
public:
	CGame();
	~CGame();

	CCamera* pCamera;

	void Init();
	void Update();
};

