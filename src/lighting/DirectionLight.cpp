#include "DirectionLight.h"
#include "window/Window.h"

DirectionLight::DirectionLight()
{
    activate();
}

void DirectionLight::draw()
{
    Window::objectShader->use();
    Window::objectShader->setVec3("dirLight.direction",direction);
    Window::objectShader->setVec3("dirLight.ambient",ambient);
    Window::objectShader->setVec3("dirLight.diffuse",diffuse);
    Window::objectShader->setVec3("dirLight.specular",specular);

    Window::lightShader->use();
    Window::lightShader->setMat4("projection",Window::camera->getProjection());
    Window::lightShader->setMat4("view",Window::camera->getView());
}

void DirectionLight::disable()
{
    Window::objectShader->use();
    Window::objectShader->setBool("isDirLight",false);
}

void DirectionLight::activate()
{
    Window::objectShader->use();
    Window::objectShader->setBool("isDirLight",true);
}