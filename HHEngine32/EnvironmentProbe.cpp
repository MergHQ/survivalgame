#include "stdafx.h"
#include "EnvironmentProbe.h"
#include "Engine.h"
#include "GlobalSystem.h"
#include "Renderer.h"
#include "RadianceGen.h"

CEnvironmentProbe::CEnvironmentProbe()
{
}

CEnvironmentProbe::~CEnvironmentProbe()
{
}

void CEnvironmentProbe::Update()
{
	if (CRenderer* pRenderer = gSys->pEngine->pRenderer)
	{
		if (pRenderer->GetRadianceGen())
		{
			pRenderer->GetRadianceGen()->Render(this);
		}
	}
}
