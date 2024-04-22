#include "PointLight.h"
#include "window/Window.h"

int PointLight::countLights = 0;

PointLight::PointLight()
{
    countLights++;
    indexLight = countLights - 1;
    indexLightStr = std::to_string(indexLight);
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
    Window::objectShader->setBool("pointLights[" + indexLightStr + "].isActive",status);

    Window::lightShader->use();
    Window::lightShader->setBool("isActive",status);
    Window::lightShader->setVec4("color",color);
    glm::mat4 mat = model;
    mat = glm::translate(mat,position);
    mat = glm::scale(mat,scale);
    mat = glm::rotate(mat,glm::radians(angle), rotate);
    Window::lightShader->setMat4("model", mat);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void PointLight::setColor(const glm::vec4 &color)
{
    this->color = color;
    diffuse = ambient = specular = color;
    Window::lightShader->use();
    Window::lightShader->setVec4("color",color);
}