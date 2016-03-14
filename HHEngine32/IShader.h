#pragma once
#include <vector>

struct IShader
{
	virtual unsigned int& GetProgramId() = 0;
	virtual std::vector<unsigned int>& GetUniforms() = 0;
};
