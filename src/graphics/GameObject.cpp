#include "GameObject.h"

#include "window/Window.h"

GameObject::GameObject()
{
    model = glm::mat4(1.0f);
    position = glm::vec3(0.0f);
}

GameObject::~GameObject()
{
    glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void GameObject::loadTexture(const std::string &texturePath)
{
    texture = load_texture(texturePath);
}

void GameObject::loadDiffuseMap(const std::string &texturePath)
{
    diffuseMap = load_texture(texturePath);
    Window::objectShader->use();
    Window::objectShader->setInt("material.diffuse", 0);
}

void GameObject::loadSpecularMap(const std::string &texturePath)
{
    specularMap = load_texture(texturePath);
    Window::objectShader->use();
    Window::objectShader->setInt("material.specular", 1);
    
}

void GameObject::loadEmissionMap(const std::string &texturePath)
{
    emissionMap = load_texture(texturePath);
    Window::objectShader->use();
    Window::objectShader->setInt("material.emission",2);
}

void GameObject::setColor(const glm::vec4 &color)
{
    this->color = color;
}

void GameObject::setPosition(const glm::vec3 &position)
{
    model = glm::translate(model,position);
    this->position = position;
}

void GameObject::setScale(const glm::vec3 &scale)
{
    model = glm::scale(model,scale);
    this->scale = scale;
}

void GameObject::setModel(const glm::mat4 &model)
{
    this->model = model;
}

GLuint GameObject::getVAO()
{
    return VAO;
}

GLuint GameObject::getVBO()
{
    return VBO;
}

glm::vec4 GameObject::getColor()
{
    return color;
}

glm::vec3 GameObject::getPosition()
{
    return position;
}
