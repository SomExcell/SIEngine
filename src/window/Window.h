#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics/Shader.h"
#include "Camera.h"

class Window
{
public:

public:
    static int Initialize(const int &width, const int &height, const char* title);
    static void Terminate();

    static void SetCursorMode(int mode);
    static bool IsShouldClose();
    static void SetShouldClose(bool flag);
    static void SwapBuffers();

    static void LoadObjectShaders(const std::string &vertexFile, const std::string &fragmentFile);
    static void LoadLightShaders(const std::string &vertexFile, const std::string &fragmentFile);
    static void LoadOutlineShaders(const std::string &vertexFile, const std::string &fragmentFile);
    static void SetCamera(Camera *camera);

    static void DisplayFPS();

    static GLFWwindow *window;

    static unsigned int width;
    static unsigned int height;

    static Shader *objectShader;
    static Shader *lightShader;
    static Shader *outlineShader;

    static Camera *camera;

    static double prevTime;
    static double currentTime;
    static double timeDiff;
    static unsigned int counter;
};

#endif