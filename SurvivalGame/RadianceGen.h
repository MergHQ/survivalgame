#pragma once
#include <Windows.h>
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>

class CGBuffer;

class CRadianceGen
{
public:
	CRadianceGen();
	~CRadianceGen();
	bool souldGenerate;
	float data[6][64 * 64 * 3];
	glm::mat4x4 shValues_r;
	glm::mat4x4 shValues_g;
	glm::mat4x4 shValues_b;
	void Render();
	void GetTexelAttrib(const int texId, const float u, const float v, const float texelSize, glm::vec3 *direction, float *solidAngle);
private:
	HANDLE m_shThread;
	CGBuffer* m_pGBuffer;


};

