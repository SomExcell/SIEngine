#include "GameObject.h"

#include "window/Window.h"

GameObject::~GameObject()
{
    delete texture;
    delete diffuseMap;
    delete specularMap;
    delete emissionMap;
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

void GameObject::setPosition(glm::vec3 position)
{
    this->position = position;
}

GLuint GameObject::getVAO()
{
    return VAO;
}

GLuint GameObject::getVBO()
{
    return VBO;
}
