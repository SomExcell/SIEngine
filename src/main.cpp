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
	Window::loadOutlineShaders("resources/shaders/outlineVS.vs","resources/shaders/outlineFS.fs");
	
	Model sphere("resources/models/shapes/sphere.obj");
	sphere.setPosition(glm::vec3(4,0,-2));
	sphere.setScale(glm::vec3(0.1));
	sphere.outline(true);
	
	
	
	Rectangle firstCube{};
    firstCube.loadDiffuseMap("resources/images/container2.png");
    firstCube.loadSpecularMap("resources/images/container2_specular.png");
	firstCube.outline = true;

	Rectangle secondCube{};
	secondCube.loadDiffuseMap("resources/images/container2.png");
    secondCube.loadSpecularMap("resources/images/container2_specular.png");
	secondCube.setPosition(glm::vec3(2,0,1));
	secondCube.outline = true;
	
	Rectangle floor{};

	floor.loadDiffuseMap("resources/images/floor.jpg");
	floor.setPosition(glm::vec3(0,-5.5,0));
	floor.setScale(glm::vec3(10));
	
	
    DirectionLight *dirLight = new DirectionLight();
	PointLight *pointLight = new PointLight();
	SpotLight *spotLight = new SpotLight();

	pointLight->setPosition(glm::vec3(0.7f,  0.2f,  2.0f));
	pointLight->setLights(glm::vec3(0.1f, 0.1f, 0.8f),glm::vec3(0.1f, 0.1f, 0.8f),glm::vec3(0.1f, 0.1f, 0.9f));
	pointLight->setColor(glm::vec4(0.5f,0.5f,0.8f,1.0f));
	pointLight->setLightRange(1.0f,0.001f,0.032f);
	pointLight->setScale(glm::vec3(0.2f));

	dirLight->setLights(glm::vec3(0.3f, 0.3f, 0.3f),glm::vec3(0.9f, 0.9f, 0.9f),glm::vec3(0.9f, 0.9f, 0.9f));
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

	glfwSwapInterval(0);

	bool switchSpotLight = true;
	bool switchDirLight = true;
	bool switchPointLight = true;
	
	while (!Window::isShouldClose()){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
		if(Events::jpressed(GLFW_KEY_Z))
		{
			firstCube.outline ? sphere.outline(false) : sphere.outline(true);
			firstCube.outline ? firstCube.outline = false : firstCube.outline = true;
		}
		
        Window::displayFPS();

        camera->move();
		spotLight->setPosition(Window::camera->position);
		spotLight->setDirection(Window::camera->front);

        dirLight->draw();
		spotLight->draw();
		pointLight->draw();

		//backpack.draw();
		
		floor.draw();
		sphere.draw();
		firstCube.draw();
		secondCube.draw();

		Window::swapBuffers();
		Events::pullEvents();
	}

	Window::terminate();
	return 0;
}