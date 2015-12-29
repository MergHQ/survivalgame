#include "Renderer.h"
#include <GLFW\glfw3.h>
#include <GL\glew.h>
#include "GlobalSystem.h"
#include "IMesh.h"
#include "StaticMesh.h"

CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
}

void CRenderer::InitDependencies()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void CRenderer::Render()
{
	ClearFrame();
	MeshPass();
}

void CRenderer::MeshPass()
{
}

void CRenderer::ClearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
}
