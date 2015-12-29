#include "Engine.h"
#include "Renderer.h"
#include "MeshSystem.h"

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
	delete pRenderer;
	delete pMeshSystem;
}

void CEngine::Init()
{
	pRenderer = new CRenderer;
	pRenderer->InitDependencies();

	pMeshSystem = new CMeshSystem;
}

void CEngine::Update()
{
	pRenderer->Render();
}
