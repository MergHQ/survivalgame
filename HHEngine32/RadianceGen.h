#pragma once
#include <Windows.h>
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>

class CGBuffer;
class CEnvironmentProbe;

struct EnvProbeThreadJob
{
	bool isDone = true;
	CEnvironmentProbe* pProbe;
};

class CRadianceGen
{
public:
	CRadianceGen();
	~CRadianceGen();
	EnvProbeThreadJob currentJob;
	void Render(CEnvironmentProbe* pProbe);
	void GetTexelAttrib(const int texId, const float u, const float v, const float texelSize, glm::vec3 *direction, float *solidAngle);
private:
	HANDLE m_shThread;
	CGBuffer* m_pGBuffer;


};

