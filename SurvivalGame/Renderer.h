#pragma once
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void InitDependencies();
	void Render();

private:
	void MeshPass();
	void ClearFrame();
};

