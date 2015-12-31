#pragma once
#include <string>
#include <time.h>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

class CGame;
class CEngine;
struct GLFWwindow;

struct SGlobalSystem
{
public:

	SGlobalSystem(GLFWwindow*);
	~SGlobalSystem();

	CGame* pGame;
	CEngine* pEngine;
	GLFWwindow* pWin;
	
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