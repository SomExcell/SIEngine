#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "graphics/stb_image.h"

GLFWwindow* Window::window = nullptr;

Shader *Window::objectShader;
Shader *Window::lightShader;

Camera *Window::camera;

unsigned int Window::width = 0;
unsigned int Window::height = 0;

int Window::initialize(int width, int height, const char* title)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    stbi_set_flip_vertically_on_load(true);
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

void Window::setCamera(Camera *camera)
{
    Window::camera = camera;
}