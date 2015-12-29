#pragma once
#include <string>
#include <time.h>
#include <glm\vec3.hpp>

class CGame;
class CEngine;

struct SGlobalSystem
{
public:

	SGlobalSystem() {};
	~SGlobalSystem();

	CGame* pGame;
	CEngine* pEngine;

	void Init();
	void Update();
	template <class T> 
	void Log(std::string text, const T& obj);
};

extern SGlobalSystem* gSys;

template<class T>
inline void SGlobalSystem::Log(std::string text, const T& obj)
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::string time = "[" + std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec) + "] ";
	std::string object = std::string(" | ") + typeid(obj).name();
	printf(std::string(time+text+object + " \n").c_str());
}

typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;