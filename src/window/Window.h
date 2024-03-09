#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"
#include "Camera.h"


class Window
{
public:
    static int initialize(const int &width, const int &height, const char* title);
    static void terminate();

    static void setCursorMode(int mode);
    static bool isShouldClose();
    static void setShouldClose(bool flag);
    static void swapBuffers();

    static void loadObjectShaders(const std::string &vertexFile, const std::string &fragmentFile);
    static void loadLightShaders(const std::string &vertexFile, const std::string &fragmentFile);
    static void setCamera(Camera *camera);

    static void displayFPS();

    static GLFWwindow *window;

    static unsigned int width;
    static unsigned int height;

    static Shader *objectShader;
    static Shader *lightShader;

    static Camera *camera;

    static double prevTime;
    static double crntTime;
    static double timeDiff;
    static unsigned int counter;
};

#endif

