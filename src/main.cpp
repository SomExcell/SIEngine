#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "window/Window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "loaders/png_loading.h"
#include "graphics/Rectangle.h"
#include "graphics/Light.h"
#include "window/FPSCounter.h"

int main() {
	Window::initialize(1280, 720, "SIEngine");
	Events::initialize();
    Camera* camera = new Camera(glm::vec3(0,0,1), glm::radians(90.0f));
    Window::setCamera(camera);

    Window::loadObjectShaders("resources/shaders/objectVS.txt","resources/shaders/objectFS.txt");
    Window::loadLightShaders("resources/shaders/lightVS.txt","resources/shaders/lightFS.txt");

	Rectangle *rectangle = new Rectangle();
    rectangle->loadDiffuseMap("resources/images/container2.png");
    rectangle->loadSpecularMap("resources/images/container2_specular.png");
    rectangle->loadEmissionMap("resources/images/texFire.png");
    
    Light *light = new Light();


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
    glEnable(GL_DEPTH_TEST);

    glm::vec3 pos;

	while (!Window::isShouldClose()){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Events::jpressed(GLFW_KEY_ESCAPE)){
		Window::setShouldClose(true);
		}
		if (Events::jpressed(GLFW_KEY_TAB)){
			Events::toogleCursor();
		}
		
        FPSCounter::displayFPS();
        camera->move();
		
        pos = glm::vec3(sin(glfwGetTime())*5,0.0f,cos(glfwGetTime())*5);

        light->setPosition(pos);

        light->draw();
        rectangle->draw();
        
		Window::swapBuffers();
		Events::pullEvents();
	}


	Window::terminate();
	return 0;
}