#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "window/Window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "loaders/png_loading.h"
#include "graphics/Rectangle.h"

int WIDTH = 1280;
int HEIGHT = 720;

void moveCamera(Camera *camera, float delta, float speed, float &camX, float &camY);

float vertices[] = {
    //positions                 //color            //texture coords
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f, //1
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,      1.0f, 0.0f, //2
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f, //3   back side
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f, //4
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,      0.0f, 1.0f, //5
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f, //6

    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//7
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//8
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//9    front side
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//10
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//11
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//12

    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//13
    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//14
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//15   left side
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//16
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//17
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//18

     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//19
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//20
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//21
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//22   right side
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//23
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//24

    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//25
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//26
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//27   down
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//28
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//29
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//30

    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//31
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//32
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//33   top
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//34
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//35
    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f};


int main() {
	Window::initialize(WIDTH, HEIGHT, "Window 2.0");
	Events::initialize();
    
	Shader* shader = load_shader("resources/shaders/vs.txt", "resources/shaders/fs.txt");
	if (shader == nullptr){
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}
    
	Texture* texture = load_texture("resources/images/container.jpg");
	if (texture == nullptr){
		std::cerr << "failed to load texture" << std::endl;
		delete shader;
		Window::terminate();
		return 1;
	}

	Rectangle *rectangle = new Rectangle();
	rectangle->loadTexture("resources/images/container.jpg","jpg");

	glClearColor(0.6f,0.62f,0.65f,1);
	
    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_DEPTH_TEST);

	Camera* camera = new Camera(vec3(0,0,1), radians(90.0f));

	mat4 model(1.0f);
	model = translate(model, vec3(0.5f,0,0));

	while (!Window::isShouldClose()){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Events::jpressed(GLFW_KEY_ESCAPE)){
		Window::setShouldClose(true);
		}
		if (Events::jpressed(GLFW_KEY_TAB)){
			Events::toogleCursor();
		}
		
		camera->move();

		// Draw VAO
		shader->use();
		shader->uniformMatrix("model", model);
		shader->uniformMatrix("projview", camera->getProjection()*camera->getView());
		texture->bind();

		rectangle->draw();
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

		Window::swapBuffers();
		Events::pullEvents();
	}

	delete shader;
	delete texture;

	Window::terminate();
	return 0;
}