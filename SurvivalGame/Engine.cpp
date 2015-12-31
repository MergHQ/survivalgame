#include "Engine.h"
#include "Renderer.h"
#include "MeshSystem.h"
#include "Input.h"
#include "TerrainGen.h"

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
	delete pRenderer;
	delete pMeshSystem;
	delete pInput;
}

void CEngine::Init()
{
	pMeshSystem = new CMeshSystem;

	pInput = new CInput;

	pRenderer = new CRenderer;
	pRenderer->InitDependencies();
}

void CEngine::Update()
{
	pRenderer->Render();
}
