#pragma once
#include <string>

struct IMesh
{
	virtual ~IMesh() = 0;
	virtual unsigned int GetMeshId() = 0;
	virtual unsigned int& GetVertexAttribArray() = 0;
	virtual std::string GetFileName() = 0;
};