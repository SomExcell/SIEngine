#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

class GLFWwindow;

class Window
{
public:
    static int initialize(int width, int height, const char* title);
    static void terminate();

    static void setCursorMode(int mode);
    static bool isShouldClose();
    static void setShouldClose(bool flag);
    static void swapBuffers();

public:
    static GLFWwindow *window;

    static unsigned int width;
    static unsigned int height;
};

#endif

