#include "DirectionLight.h"
#include "window/Window.h"

DirectionLight::DirectionLight(){}

void DirectionLight::draw()
{
    Window::objectShader->use();
    Window::objectShader->setVec3("dirLight.direction",direction);
    Window::objectShader->setVec3("dirLight.ambient",ambient);
    Window::objectShader->setVec3("dirLight.diffuse",diffuse);
    Window::objectShader->setVec3("dirLight.specular",specular);
    Window::objectShader->setBool("isDirLight",status);
    if(status){glClearColor(0.5f,0.5f,0.5f,1.0f);}
    else {glClearColor(0.2f,0.2f,0.2f,1.0f);}
    

}