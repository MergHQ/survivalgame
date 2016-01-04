#pragma once
#include <glm\common.hpp>
#include <vector>
#include <GL\glew.h>

class CSSAO
{
public:
	CSSAO();
	~CSSAO();
	
	void SendUniforms(GLuint uniform1, GLuint uniform2, GLuint uniform3, GLuint uniform4);
	float radius = 1.f;
private:
	float lerp(float a, float b, float f) { return a + f * (b - a); }
	std::vector<glm::vec3> m_kernelPoints;
	std::vector<glm::vec3> m_ssaoNoise;
	int m_kernelSize;
	GLuint m_noiseTextureId;
};

