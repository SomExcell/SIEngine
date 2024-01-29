#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/Window.h"
#include "window/Events.h"

int main()
{
    Window::initialize(800,600,"SIEngine");
    Events::initialize();

    glClearColor(0.0f,0.3,0.9f,1.0f);

    while (!Window::isShouldClose())
    {
        glfwPollEvents();
        
        if (Events::jpressed(GLFW_KEY_ESCAPE)){
			Window::setShouldClose(true);
		}
        
        glClear(GL_COLOR_BUFFER_BIT);

        Window::swapBuffers();
    }

    Window::terminate();
    return 0;
}
