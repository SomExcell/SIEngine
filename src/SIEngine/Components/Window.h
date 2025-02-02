#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "SIEngine/GraphicsAPI/OpenGL/Shader.h"
#include "Camera.h"

class Window
{
public:
    static int Initialize(const int &width, const int &height, const char* title);
    static void Terminate();

    static void SetCursorMode(int mode);
    static bool IsShouldClose();
    static void SetShouldClose(bool value);
    static void SwapBuffers();

    static void SetCamera(Camera *camera);

    static void DisplayFPS();

    static GLFWwindow *window;

    static unsigned int width;
    static unsigned int height;

    static double prevTime;
    static double currentTime;
    static double timeDiff;
    static unsigned int counter;
};

#endif