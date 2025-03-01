#include "GameObject.h"

#include "SIEngine/Components/Window.h"

GameObject::GameObject()
{
    model = glm::mat4(1.0f);
    position = glm::vec3(0.0f);
}

GameObject::~GameObject() = default;

void GameObject::draw()
{
    //Window::objectShader->Use();
    //Window::objectShader->SetFloat("material.shininess",32.0f);
    glm::mat4 mat = model;
    mat = glm::translate(mat,position);
    mat = glm::scale(mat,scale);
    mat = glm::rotate(mat,glm::radians(angle), rotate);

    //Window::objectShader->SetMat4("model", mat);
    glBindVertexArray(VAO);
    if(diffuseMap)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap->GetId());
    }
    else
    {
        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
    }

    if(specularMap)
    {
        glActiveTexture(GL_TEXTURE1);
	    glBindTexture(GL_TEXTURE_2D, specularMap->GetId());
    }else
    {
        glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
    }

    if(emissionMap)
    {
        glActiveTexture(GL_TEXTURE2);
	    glBindTexture(GL_TEXTURE_2D, emissionMap->GetId());
    }
    else
    {
        glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
    }

}

void GameObject::loadTexture(const std::string &texturePath)
{
    texture = new Texture(texturePath);
}

void GameObject::loadDiffuseMap(const std::string &texturePath)
{
    diffuseMap = new Texture(texturePath);
    //Window::objectShader->Use();
    //Window::objectShader->SetInt("material.diffuse", 0);
}

void GameObject::loadSpecularMap(const std::string &texturePath)
{
    specularMap = new Texture(texturePath);
    /*Window::objectShader->Use();
    Window::objectShader->SetInt("material.specular", 1);*/

}

void GameObject::loadEmissionMap(const std::string &texturePath)
{
    emissionMap = new Texture(texturePath);
    /*Window::objectShader->Use();
    Window::objectShader->SetInt("material.emission", 2);*/
}

void GameObject::setColor(const glm::vec4 &color)
{
    this->color = color;
}

void GameObject::setPosition(const glm::vec3 &position)
{
    this->position = position;
}

void GameObject::setScale(const glm::vec3 &scale)
{
    this->scale = scale;
}

void GameObject::setRotate(const float& angle, const glm::vec3 &rotate)
{
    this->angle = angle;
    this->rotate = rotate;
}

void GameObject::setModel(const glm::mat4 &model)
{
    this->model = model;
}

glm::vec3 GameObject::getPosition()
{
    return position;
}

glm::vec3 GameObject::getScale()
{
    return scale;
}

glm::mat4 GameObject::getModel()
{
    return model;
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

void GameObject::flipTexture(bool state)
{
    _flipTexture = state;
}
