#include "SpotLight.h"
#include "SIEngine/Components/Window.h"

int SpotLight::countLights = 0;

SpotLight::SpotLight()
{
    countLights++;
    indexLight = countLights - 1;
    indexLightStr = std::to_string(indexLight);
    //Window::objectShader->Use();
    //Window::objectShader->SetInt("countSpotLights", countLights);

}

void SpotLight::draw()
{
    /*Window::objectShader->Use();
    Window::objectShader->SetVec3("spotLights[" + indexLightStr + "].position", position);
    Window::objectShader->SetVec3("spotLights[" + indexLightStr + "].direction", direction);
    Window::objectShader->SetVec3("spotLights[" + indexLightStr + "].ambient", ambient);
    Window::objectShader->SetVec3("spotLights[" + indexLightStr + "].diffuse", diffuse);
    Window::objectShader->SetVec3("spotLights[" + indexLightStr + "].specular", specular);
    Window::objectShader->SetFloat("spotLights[" + indexLightStr + "].constant", constant);
    Window::objectShader->SetFloat("spotLights[" + indexLightStr + "].linear", linear);
    Window::objectShader->SetFloat("spotLights[" + indexLightStr + "].quadratic", quadratic);
    Window::objectShader->SetFloat("spotLights[" + indexLightStr + "].cutOff", glm::cos(glm::radians(cutOff)));
    Window::objectShader->SetFloat("spotLights[" + indexLightStr + "].outerCutOff", glm::cos(glm::radians(outerCutOff)));
    Window::objectShader->SetBool("spotLights[" + indexLightStr + "].isActive", status);

    Window::lightShader->Use();*/
    //Window::lightShader->setMat4("model", model);
}