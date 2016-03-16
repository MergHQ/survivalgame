#pragma once

struct IInputListener;
struct GLFWwindow;
#include <vector>

class __declspec(dllexport) CInput
{
public:
	CInput();
	~CInput();

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void addListener(IInputListener *listener);
	void addListener(IInputListener *listener, int index);
	void removeListener(const IInputListener* listener);
	void clearListeners();
private:
	std::vector<IInputListener*> listeners;
};
