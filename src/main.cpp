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
#include "lighting/DirectionLight.h"
#include "lighting/PointLight.h"
#include "lighting/SpotLight.h"
#include "graphics/Model.h"

int main() {
	Window::initialize(1280, 720, "SIEngine");
	Events::initialize();
    Camera* camera = new Camera(glm::vec3(0,0,1), glm::radians(90.0f));
    Window::setCamera(camera);
	
    Window::loadObjectShaders("resources/shaders/objectVS.vs","resources/shaders/objectFS.fs");
    Window::loadLightShaders("resources/shaders/lightVS.vs","resources/shaders/lightFS.fs");

	//Model model("resources/models/backpack/backpack.obj");
	Model sphere("resources/models/shapes/sphere.obj");
	
	sphere.setScale(glm::vec3(0.1));


	Rectangle *rectangle = new Rectangle();
    rectangle->loadDiffuseMap("resources/images/container2.png");
    rectangle->loadSpecularMap("resources/images/container2_specular.png");

    DirectionLight *dirLight = new DirectionLight();
	PointLight *pointLight = new PointLight();
	SpotLight *spotLight = new SpotLight();

	pointLight->setPosition(glm::vec3(0.7f,  0.2f,  2.0f));
	pointLight->setLights(glm::vec3(0.1f, 0.1f, 0.8f),glm::vec3(0.1f, 0.1f, 0.8f),glm::vec3(0.1f, 0.1f, 0.9f));
	pointLight->setColor(glm::vec4(0.5f,0.5f,0.8f,1.0f));
	pointLight->setLightRange(1.0f,0.001f,0.032f);
	pointLight->setScale(glm::vec3(0.2f));

	dirLight->setLights(glm::vec3(0.3f, 0.3f, 0.3f),glm::vec3(0.9f, 0.9f, 0.9f),glm::vec3(0.9f, 0.9f, 0.9f));

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
    glEnable(GL_DEPTH_TEST);

	glfwSwapInterval(0);

	bool switchSpotLight = true;
	bool switchDirLight = true;
	bool switchPointLight = true;
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!Window::isShouldClose()){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Events::jpressed(GLFW_KEY_ESCAPE)){
		Window::setShouldClose(true);
		}
		if (Events::jpressed(GLFW_KEY_TAB)){
			Events::toogleCursor();
		}
		if(Events::jpressed(GLFW_KEY_O))
		{
			switchSpotLight ? spotLight->disable() : spotLight->activate();
			switchSpotLight ? switchSpotLight = false : switchSpotLight = true;
		}
		if(Events::jpressed(GLFW_KEY_P))
		{
			switchDirLight ? dirLight->disable() : dirLight->activate();
			switchDirLight ? switchDirLight = false : switchDirLight = true;
		}
		if(Events::jpressed(GLFW_KEY_I))
		{
			switchPointLight ? pointLight->disable() : pointLight->activate();
			switchPointLight ? switchPointLight = false : switchPointLight = true;
		}

        Window::displayFPS();
        camera->move();
		spotLight->setPosition(Window::camera->position);
		spotLight->setDirection(Window::camera->front);

        dirLight->draw();
		spotLight->draw();
		pointLight->draw();

		sphere.setPosition(glm::vec3(sin(glfwGetTime())*0.01,0,0));
		//rectangle->draw();
        sphere.draw();


		Window::swapBuffers();
		Events::pullEvents();
	}


	Window::terminate();
	return 0;
}