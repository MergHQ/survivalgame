#pragma once

struct IShader;
struct IMesh;

class CSkyBox
{
public:
	CSkyBox();
	~CSkyBox();

	void Draw();

	IMesh* m_pMesh;
};

