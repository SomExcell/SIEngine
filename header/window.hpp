#pragma once

#include <camera.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint SIZEX = 800;
GLuint SIZEY = 600;

GLfloat lastX = SIZEX / 2.0f;
GLfloat lastY = SIZEY / 2.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLboolean firstMouse = true;
GLboolean keys[1024];

Camera camera{};

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void doMovement();
void glfwMouseCallback(GLFWwindow *window, GLdouble xposIn, GLdouble yposIn);
void glfwScrollCallback(GLFWwindow *window, GLdouble xoffset, GLdouble yoffset);

class Window
{
public:
    Window();
    ~Window(){};

    void swapBuffers();
    GLboolean closed();

private:
    GLuint sizeX = SIZEX;
    GLuint sizeY = SIZEY;
    GLFWwindow *window;
};

Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit())
    {
        std::cerr << "ERROR glfw load" << std::endl;
    }

    window = glfwCreateWindow(sizeX, sizeY, "SIEngine", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "ERROR window is not created" << std::endl;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetCursorPosCallback(window,glfwMouseCallback);
    glfwSetScrollCallback(window,glfwScrollCallback);
    
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version:" << glGetString(GL_VERSION)  << std::endl;
    glEnable(GL_DEPTH_TEST); 
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

GLboolean Window::closed()
{
    return glfwWindowShouldClose(window);
}



void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    SIZEX = width;
    SIZEY = height;
    glViewport(0, 0, SIZEY, SIZEX);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }

    if(action == GLFW_PRESS)
    {
        keys[key] = true;
    }else if(action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}

void doMovement()
{
    if(keys[GLFW_KEY_W]){camera.ProcessKeyBoard(FORWARD,deltaTime);}
    if(keys[GLFW_KEY_S]){camera.ProcessKeyBoard(BACKWARD,deltaTime);}
    if(keys[GLFW_KEY_A]){camera.ProcessKeyBoard(LEFT,deltaTime);}
    if(keys[GLFW_KEY_D]){camera.ProcessKeyBoard(RIGHT,deltaTime);}
}

void glfwMouseCallback(GLFWwindow *window, GLdouble xposIn, GLdouble yposIn)
{
    GLfloat xpos = static_cast<GLfloat>(xposIn);
    GLfloat ypos = static_cast<GLfloat>(yposIn);

    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset,yoffset);
}

void glfwScrollCallback(GLFWwindow *window, GLdouble xoffset, GLdouble yoffset)
{
    camera.ProcessMouseScroll(static_cast<GLfloat>(yoffset));
}

