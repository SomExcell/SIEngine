#include "SpotLight.h"
#include "window/Window.h"

int SpotLight::countLights = 0;

SpotLight::SpotLight()
{
    countLights++;
    indexLight = countLights - 1;
    indexLightStr = std::to_string(indexLight);
    activate();
    Window::objectShader->use();
    Window::objectShader->setInt("countSpotLights",countLights);

}

void SpotLight::draw()
{
    Window::objectShader->use();
    Window::objectShader->setVec3("spotLights[" + indexLightStr + "].position", position);
    Window::objectShader->setVec3("spotLights[" + indexLightStr + "].direction", direction);
    Window::objectShader->setVec3("spotLights[" + indexLightStr + "].ambient", ambient);
    Window::objectShader->setVec3("spotLights[" + indexLightStr + "].diffuse", diffuse);
    Window::objectShader->setVec3("spotLights[" + indexLightStr + "].specular", specular);
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].constant", constant);
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].linear", linear);
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].quadratic", quadratic);
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].cutOff", glm::cos(glm::radians(12.5f)));
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].outerCutOff", glm::cos(glm::radians(15.0f)));

    Window::lightShader->use();
    Window::lightShader->setMat4("projection",Window::camera->getProjection());
    Window::lightShader->setMat4("view",Window::camera->getView());
    //Window::lightShader->setMat4("model", model);
}

void SpotLight::disable()
{
    Window::objectShader->use();
    Window::objectShader->setBool("spotLights[" + indexLightStr + "].isActive",false);
}

void SpotLight::activate()
{
    Window::objectShader->use();
    Window::objectShader->setBool("spotLights[" + indexLightStr + "].isActive",true);
}