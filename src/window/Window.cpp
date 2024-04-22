#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "graphics/stb_image.h"

GLFWwindow* Window::window = nullptr;

Shader *Window::objectShader;
Shader *Window::lightShader;
Shader *Window::outlineShader;

Camera *Window::camera = nullptr;

unsigned int Window::width = 0;
unsigned int Window::height = 0;

unsigned int Window::counter = 0;
double Window::prevTime = glfwGetTime();
double Window::crntTime = 0.0;
double Window::timeDiff = 0.0;

int Window::initialize(const int &width, const int &height, const char* title)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Failed to create GLFW Window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0, width, height);

	Window::width = width;
	Window::height = height;
	return 0;
}

void Window::setCursorMode(int mode)
{
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void Window::terminate()
{
	glfwTerminate();
}

bool Window::isShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag)
{
	glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::loadObjectShaders(const std::string &vertexFile, const std::string &fragmentFile)
{
    objectShader = load_shader(vertexFile,fragmentFile);
}

void Window::loadLightShaders(const std::string &vertexFile, const std::string &fragmentFile)
{
    lightShader = load_shader(vertexFile,fragmentFile);
}

void Window::loadOutlineShaders(const std::string &vertexFile, const std::string &fragmentFile)
{
    outlineShader = load_shader(vertexFile,fragmentFile);
}

void Window::setCamera(Camera *camera)
{
    Window::camera = camera;
}

void Window::displayFPS()
{
    crntTime = glfwGetTime();
    timeDiff = crntTime - prevTime;
    counter++;
    if(timeDiff >= 1.0 / 30.0)
    {
        std::string FPS = std::to_string((1.0 / timeDiff) * counter);
        std::string ms = std::to_string((timeDiff / counter) * 1000);
        std::string newTitle = "SIEngine - " + FPS + "FPS / " + ms + "ms";
        glfwSetWindowTitle(Window::window, newTitle.c_str());
        counter = 0;
        prevTime = crntTime;
        
    }
}