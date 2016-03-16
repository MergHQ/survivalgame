#include "stdafx.h"
#include "Engine.h"
#include "Renderer.h"
#include "MeshSystem.h"
#include "Input.h"
#include "CameraSystem.h"

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
	delete pRenderer;
	delete pMeshSystem;
	delete pInput;
	delete pCamSys;
}

void CEngine::Init()
{
	pMeshSystem = new CMeshSystem;

	pInput = new CInput;

	pCamSys = new CCameraSystem;
	pRenderer = new CRenderer;
	pRenderer->InitDependencies();
}

void CEngine::Update()
{
	pRenderer->Render();
	pCamSys->Update();
}
 