#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <mutex>

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
#include "Engine/IGame.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

void checkKeys();

void drawFloor(Rectangle &floor);
void drawSphers(Model &sphere);


int main()
{
    //Engine::Run(std::unique_ptr<IGame>{new Game{}});

    Window::Initialize(1280, 720, "SIEngine");
	Events::initialize();
    Camera* firstCamera = new Camera(glm::vec3(0,0,1), glm::radians(60.0f));
	Camera* secondCamera = new Camera(glm::vec3(25,10,25),glm::radians(60.0f));
	//secondCamera->rotate(90,0,90);
    Window::SetCamera(firstCamera);

    Window::LoadObjectShaders("resources/shaders/objectVS.vs", "resources/shaders/objectFS.fs");
    Window::LoadLightShaders("resources/shaders/lightVS.vs", "resources/shaders/lightFS.fs");
    Window::LoadOutlineShaders("resources/shaders/outlineVS.vs", "resources/shaders/outlineFS.fs");
	
	Model sphere("resources/models/shapes/sphere.obj");

	Model storm("resources/models/storm/storm.obj");
	storm.setPosition(glm::vec3(10,-0.5f,0));
	storm.setFlipTexture(false);

	Model planet("resources/models/planet/saturn2/planet.obj");
	planet.setScale(glm::vec3(3));
	planet.setPosition(glm::vec3(10,20,10));

	Model spaceship("resources/models/spaceship/spaceship.obj");
	spaceship.setScale(glm::vec3(0.1));
	spaceship.setPosition(glm::vec3(0,0,10));
	
	Rectangle firstCube{};
    firstCube.loadDiffuseMap("resources/images/container2.png");
    firstCube.loadSpecularMap("resources/images/container2_specular.png");
	firstCube.setPosition(glm::vec3(-1,0,-2));

	Rectangle secondCube{};
	secondCube.loadDiffuseMap("resources/images/container2.png");
    secondCube.loadSpecularMap("resources/images/container2_specular.png");
	secondCube.setPosition(glm::vec3(3,0.5,2));
	secondCube.setScale(glm::vec3(2));

	Rectangle emisionCube{};
	emisionCube.loadSpecularMap("resources/images/container2_specular.png");
	emisionCube.loadEmissionMap("resources/images/texFire.png");
	emisionCube.setPosition(glm::vec3(10,0,20));

	Rectangle matCube{};
	matCube.loadSpecularMap("resources/images/container2_specular.png");
	matCube.loadEmissionMap("resources/images/matrix.jpg");
	matCube.setPosition(glm::vec3(12,0.5,18));
	matCube.setScale(glm::vec3(2));
	
	Rectangle floor{};
	floor.loadDiffuseMap("resources/images/floor.jpg");
	
    DirectionLight dirLight{};
	PointLight blueLight{};
	SpotLight spotLight{};
	spotLight.setOuterCutOff(30.0f);
	spotLight.setcutOff(20.0f);
	spotLight.setLightRange(1.0f,0.001f,0.032f);

	blueLight.setPosition(glm::vec3(0.7f,  0.2f,  2.0f));
	blueLight.setColor(glm::vec4(0.2f,0.2f,0.8f,1.0f));
	blueLight.setLightRange(1.0f,0.001f,0.032f);
	blueLight.setScale(glm::vec3(0.2f));

	PointLight redLight{};
	redLight.setPosition(glm::vec3(10,  2,  10));
	redLight.setColor(glm::vec4(0.9f,0.2f,0.2f,1.0f));
	redLight.setLightRange(1.0f,0.001f,0.032f);
	redLight.setScale(glm::vec3(0.2f));

	PointLight greenLight{};
	greenLight.setPosition(glm::vec3(20,  0.2f,  20));
	greenLight.setColor(glm::vec4(0.2f,0.9f,0.2f,1.0f));
	greenLight.setLightRange(1.0f,0.001f,0.032f);
	greenLight.setScale(glm::vec3(0.2f));

	PointLight skyLight{};
	skyLight.setLightRange(1.0f,0.001f,0.032f);
	skyLight.setScale(glm::vec3(0.2f));

	dirLight.setLights(glm::vec3(0.3f, 0.3f, 0.3f),glm::vec3(0.9f, 0.9f, 0.9f),glm::vec3(0.9f, 0.9f, 0.9f));
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

	glfwSwapInterval(0);

	bool switchSpotLight = true;
	bool switchDirLight = true;
	int switchPointLight = 1;
	int  numCamera = 0;
	while (!Window::IsShouldClose()){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if(Events::jpressed(GLFW_KEY_SPACE))
		{
			numCamera+=1;
			numCamera%3 == 0?numCamera = 1 :numCamera%=3;
			if(numCamera == 1)
			{
                Window::SetCamera(firstCamera);
			}else if(numCamera == 2)
			{
                Window::SetCamera(secondCamera);
			}
			
		}
		if (Events::jpressed(GLFW_KEY_ESCAPE)){
            Window::SetShouldClose(true);
		}
		if (Events::jpressed(GLFW_KEY_TAB))
		{
			Events::toogleCursor();
		}
		if(Events::jpressed(GLFW_KEY_O))
		{
			switchSpotLight ? spotLight.switcher(false) : spotLight.switcher(true);
			switchSpotLight ? switchSpotLight = false : switchSpotLight = true;
		}
		if(Events::jpressed(GLFW_KEY_R))
		{
			firstCamera->fov += 0.1;
		}
		if(Events::jpressed(GLFW_KEY_T))
		{
			firstCamera->fov -= 0.1;
		}
		if(Events::jpressed(GLFW_KEY_P))
		{
			switchDirLight ? dirLight.switcher(false) : dirLight.switcher(true);
			switchDirLight ? switchDirLight = false : switchDirLight = true;
		}
		if(Events::jpressed(GLFW_KEY_I))
		{
			switchPointLight = (switchPointLight+1)%5;
			if(switchPointLight == 1){blueLight.switcher(true);redLight.switcher(false);greenLight.switcher(false);}
			else if(switchPointLight == 2){blueLight.switcher(false);redLight.switcher(true);greenLight.switcher(false);}
			else if(switchPointLight == 3){blueLight.switcher(false);redLight.switcher(false);greenLight.switcher(true);}
			else if(switchPointLight == 4){blueLight.switcher(false);redLight.switcher(false);greenLight.switcher(false);}
			else {blueLight.switcher(true);redLight.switcher(true);greenLight.switcher(true);}
		}
	
		if(Events::jpressed(GLFW_KEY_Z))
		{
			firstCube.outline ? sphere.outline(false) : sphere.outline(true);
			firstCube.outline ? firstCube.outline = false : firstCube.outline = true;
		}

        Window::DisplayFPS();

        Window::camera->move();
		spotLight.setPosition(Window::camera->position);
		spotLight.setDirection(Window::camera->front);

        dirLight.draw();
		spotLight.draw();

		blueLight.draw();
		redLight.draw();
		greenLight.draw();

		skyLight.setColor(glm::vec4(0.3+abs(sin(glfwGetTime()))*0.6,0.3 + abs(cos(glfwGetTime()))*0.6,0.3 + abs(cos(glfwGetTime()))*0.6,1));
		skyLight.setPosition(glm::vec3(sin(glfwGetTime()*3)*3,sin(glfwGetTime())*3+5,cos(glfwGetTime()*3)*3+20));
		skyLight.draw();
		
		storm.draw();
		planet.draw();
		spaceship.draw();

		emisionCube.draw();

        Window::objectShader->Use();
        Window::objectShader->SetFloat("time", glfwGetTime());
        Window::objectShader->SetBool("moveTex", true);
		matCube.draw();
        Window::objectShader->SetBool("moveTex", false);
		
		firstCube.draw();
		secondCube.draw();

		drawSphers(sphere);
		drawFloor(floor);

        Window::SwapBuffers();
		Events::pullEvents();
	}

    Window::Terminate();
	return 0;
}

void drawFloor(Rectangle &floor)
{
	floor.setScale(glm::vec3(10.0f));
	for (float i = 0; i < 3; i++)
	{
		for (float j = 0; j < 3; j++)
		{
			floor.setPosition(glm::vec3(i*10,-5.5f,j*10));
			floor.draw();
		}
	}
}

void drawSphers(Model &sphere)
{
	sphere.setPosition(glm::vec3(20,5,0));
	sphere.setScale(glm::vec3(sin((float)glfwGetTime())*0.5));
	sphere.draw();
}
