#include "PointLight.h"
#include "window/Window.h"

int PointLight::cLights = 0;
std::string PointLight::countLights = "";

PointLight::PointLight()
{
    activate();
}

void PointLight::draw()
{
    Window::objectShader->use();
    Window::objectShader->setVec3("pointLights[0].position", position);
    Window::objectShader->setVec3("pointLights[0].ambient", ambient);
    Window::objectShader->setVec3("pointLights[0].diffuse", diffuse);
    Window::objectShader->setVec3("pointLights[0].specular", specular);
    Window::objectShader->setFloat("pointLights[0].constant", constant);
    Window::objectShader->setFloat("pointLights[0].linear", linear);
    Window::objectShader->setFloat("pointLights[0].quadratic", quadratic);

    Window::lightShader->use();
    Window::lightShader->setMat4("projection",Window::camera->getProjection());
    Window::lightShader->setMat4("view",Window::camera->getView());
    Window::lightShader->setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void PointLight::disable()
{
    Window::objectShader->use();
    Window::objectShader->setBool("countPointLight",0);
}

void PointLight::activate()
{
    Window::objectShader->use();
    Window::objectShader->setBool("countPointLight",1);
}