#include "SpotLight.h"
#include "window/Window.h"

SpotLight::SpotLight()
{
    activate();
}

void SpotLight::draw()
{
    Window::objectShader->use();
    Window::objectShader->setVec3("spotLight.position", position);
    Window::objectShader->setVec3("spotLight.direction", direction);
    Window::objectShader->setVec3("spotLight.ambient", ambient);
    Window::objectShader->setVec3("spotLight.diffuse", diffuse);
    Window::objectShader->setVec3("spotLight.specular", specular);
    Window::objectShader->setFloat("spotLight.constant", constant);
    Window::objectShader->setFloat("spotLight.linear", linear);
    Window::objectShader->setFloat("spotLight.quadratic", quadratic);
    Window::objectShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    Window::objectShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    Window::lightShader->use();
    Window::lightShader->setMat4("projection",Window::camera->getProjection());
    Window::lightShader->setMat4("view",Window::camera->getView());
    //Window::lightShader->setMat4("model", model);
}

void SpotLight::disable()
{
    Window::objectShader->use();
    Window::objectShader->setBool("isSpotLight",false);
}

void SpotLight::activate()
{
    Window::objectShader->use();
    Window::objectShader->setBool("isSpotLight",true);
}