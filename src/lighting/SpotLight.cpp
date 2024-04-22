#include "SpotLight.h"
#include "window/Window.h"

int SpotLight::countLights = 0;

SpotLight::SpotLight()
{
    countLights++;
    indexLight = countLights - 1;
    indexLightStr = std::to_string(indexLight);
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
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].cutOff", glm::cos(glm::radians(cutOff)));
    Window::objectShader->setFloat("spotLights[" + indexLightStr + "].outerCutOff", glm::cos(glm::radians(outerCutOff)));
    Window::objectShader->setBool("spotLights[" + indexLightStr + "].isActive",status);

    Window::lightShader->use();
    //Window::lightShader->setMat4("model", model);
}