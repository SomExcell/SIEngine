#ifndef GRAPHICS_GAMEOBJECT_H_
#define GRAPHICS_GAMEOBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#include "Texture.h"
#include "Shader.h"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void loadTexture(const std::string &texturePath);
    virtual void loadDiffuseMap(const std::string &texturePath);
    virtual void loadSpecularMap(const std::string &texturePath);
    virtual void loadEmissionMap(const std::string &texturePath);

    virtual void draw() = 0;
    virtual void setColor(const glm::vec4 &color);

    virtual void setPosition(const glm::vec3 &position);
    virtual void setScale(const glm::vec3 &scale);
    virtual void setModel(const glm::mat4 &model);
    virtual void setRotate(const float &angle, const glm::vec3 &rotate);

    virtual GLuint getVAO();
    virtual GLuint getVBO();

    virtual glm::vec4 getColor();
    virtual glm::vec3 getPosition();

protected:
    virtual void setVertices(){};
    virtual void setupBufferVertex(){};

protected:
    Texture* texture;
    Texture* diffuseMap;
    Texture* specularMap;
    Texture* emissionMap;

    unsigned int VBO = 0, VAO = 0, EBO = 0;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotate;
    float angle;
    glm::mat4 model;

    glm::vec4 color;
};

#endif