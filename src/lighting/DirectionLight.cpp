#include "DirectionLight.h"
#include "window/Window.h"

DirectionLight::DirectionLight(){}

void DirectionLight::draw()
{
    Window::objectShader->Use();
    Window::objectShader->SetVec3("dirLight.direction", direction);
    Window::objectShader->SetVec3("dirLight.ambient", ambient);
    Window::objectShader->SetVec3("dirLight.diffuse", diffuse);
    Window::objectShader->SetVec3("dirLight.specular", specular);
    Window::objectShader->SetBool("isDirLight", status);
    if(status){glClearColor(0.5f,0.5f,0.5f,1.0f);}
    else {glClearColor(0.2f,0.2f,0.2f,1.0f);}
    

}