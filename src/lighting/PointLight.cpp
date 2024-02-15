#include "PointLight.h"
#include "window/Window.h"

int PointLight::countLights = 0;

PointLight::PointLight()
{
    countLights++;
    indexLight = countLights - 1;
    indexLightStr = std::to_string(indexLight);
    activate();
    Window::objectShader->use();
    Window::objectShader->setInt("countPointLights",countLights);
}

void PointLight::draw()
{
    Window::objectShader->use();
    Window::objectShader->setVec3("pointLights[" + indexLightStr + "].position", position);
    Window::objectShader->setVec3("pointLights[" + indexLightStr + "].ambient", ambient);
    Window::objectShader->setVec3("pointLights[" + indexLightStr + "].diffuse", diffuse);
    Window::objectShader->setVec3("pointLights[" + indexLightStr + "].specular", specular);
    Window::objectShader->setFloat("pointLights[" + indexLightStr +"].constant", constant);
    Window::objectShader->setFloat("pointLights[" + indexLightStr +"].linear", linear);
    Window::objectShader->setFloat("pointLights[" + indexLightStr + "].quadratic", quadratic);

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
    Window::objectShader->setBool("pointLights[" + indexLightStr + "].isActive",false);

    Window::lightShader->use();
    Window::lightShader->setBool("isActive",false);
}

void PointLight::activate()
{
    Window::objectShader->use();
    Window::objectShader->setBool("pointLights[" + indexLightStr + "].isActive",true);

    Window::lightShader->use();
    Window::lightShader->setBool("isActive",true);
}

void PointLight::setColor(const glm::vec4 &color)
{
    Window::lightShader->use();
    Window::lightShader->setVec4("color",color);
}