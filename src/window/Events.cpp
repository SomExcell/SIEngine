#include "Events.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string.h>

bool* Events::_keys;
uint* Events::_frames;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

#define _MOUSE_BUTTONS 1024

void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
	if (Events::_cursor_started){
		Events::deltaX += xpos-Events::x;
		Events::deltaY += ypos-Events::y;
	}
	else {
		Events::_cursor_started = true;
	}
	Events::x = xpos;
	Events::y = ypos;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS){
		Events::_keys[_MOUSE_BUTTONS+button] = true;
		Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
	}
	else if (action == GLFW_RELEASE){
		Events::_keys[_MOUSE_BUTTONS+button] = false;
		Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS){
		Events::_keys[key] = true;
		Events::_frames[key] = Events::_current;
	}
	else if (action == GLFW_RELEASE){
		Events::_keys[key] = false;
		Events::_frames[key] = Events::_current;
	}
}

void WindowSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0,0, width, height);
	Window::width = width;
	Window::height = height;
}

int Events::initialize(){
	GLFWwindow* window = Window::window;
	_keys = new bool[1032];
	_frames = new uint[1032];

	memset(_keys, false, 1032*sizeof(bool));
	memset(_frames, 0, 1032*sizeof(uint));

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetWindowSizeCallback(window, WindowSizeCallback);
	return 0;
}

bool Events::pressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool Events::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::clicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index];
}

bool Events::jclicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index] && _frames[index] == _current;
}

void Events::toogleCursor(){
	_cursor_locked = !_cursor_locked;
    Window::SetCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Events::pullEvents(){
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
	updateCameraCoordinatesInShaders();
}

void Events::updateCameraCoordinatesInShaders()
{
	/*Window::outlineShader->Use();
    Window::outlineShader->SetMat4("view", Window::camera->getView());
    Window::outlineShader->SetMat4("projection", Window::camera->getProjection());

	Window::objectShader->Use();
    Window::objectShader->SetMat4("view", Window::camera->getView());
    Window::objectShader->SetMat4("projection", Window::camera->getProjection());
    Window::objectShader->SetVec3("viewPos", Window::camera->position);

	Window::lightShader->Use();
    Window::lightShader->SetMat4("projection", Window::camera->getProjection());
    Window::lightShader->SetMat4("view", Window::camera->getView());*/
}