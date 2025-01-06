#include "PointLight.h"
#include "window/Window.h"

int PointLight::countLights = 0;

PointLight::PointLight()
{
    countLights++;
    indexLight = countLights - 1;
    indexLightStr = std::to_string(indexLight);
    Window::objectShader->Use();
    Window::objectShader->SetInt("countPointLights", countLights);
    
}

void PointLight::draw()
{
    Window::objectShader->Use();
    Window::objectShader->SetVec3("pointLights[" + indexLightStr + "].position", position);
    Window::objectShader->SetVec3("pointLights[" + indexLightStr + "].ambient", ambient);
    Window::objectShader->SetVec3("pointLights[" + indexLightStr + "].diffuse", diffuse);
    Window::objectShader->SetVec3("pointLights[" + indexLightStr + "].specular", specular);
    Window::objectShader->SetFloat("pointLights[" + indexLightStr + "].constant", constant);
    Window::objectShader->SetFloat("pointLights[" + indexLightStr + "].linear", linear);
    Window::objectShader->SetFloat("pointLights[" + indexLightStr + "].quadratic", quadratic);
    Window::objectShader->SetBool("pointLights[" + indexLightStr + "].isActive", status);

    Window::lightShader->Use();
    Window::lightShader->SetBool("isActive", status);
    Window::lightShader->SetVec4("color", color);
    glm::mat4 mat = model;
    mat = glm::translate(mat,position);
    mat = glm::scale(mat,scale);
    mat = glm::rotate(mat,glm::radians(angle), rotate);
    Window::lightShader->SetMat4("model", mat);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void PointLight::setColor(const glm::vec4 &color)
{
    this->color = color;
    diffuse = ambient = specular = color;
    Window::lightShader->Use();
    Window::lightShader->SetVec4("color", color);
}