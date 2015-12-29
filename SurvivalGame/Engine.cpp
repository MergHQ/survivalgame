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

	CTerrainGen tg;
	tg.GenerateTerrain(1024, 1024, 2.0, 12.0, 1.0, 18.0);
}

void CEngine::Update()
{
	pRenderer->Render();
}
