#include "FPSCounter.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

double FPSCounter::prevTime = 0.0;
double FPSCounter::crntTime = 0.0;
double FPSCounter::timeDiff = 0.0;
unsigned int FPSCounter::counter = 0;

void FPSCounter::displayFPS()
{
    crntTime = Window::camera->currentTime;
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