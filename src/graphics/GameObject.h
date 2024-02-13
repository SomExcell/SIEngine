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

    virtual void setVertices() = 0;
    virtual void setupBufferVertex() = 0;

    virtual void draw() = 0;
    virtual void setColor(glm::vec4 color);

    virtual void setPosition(glm::vec3 position);
    virtual void setScale(glm::vec3 scale);
    virtual void setModel(glm::mat4 model);

    virtual GLuint getVAO();
    virtual GLuint getVBO();
protected:
    Texture *texture;
    Texture *diffuseMap;
    Texture *specularMap;
    Texture *emissionMap;

    GLuint VAO,VBO;

    glm::vec3 position;
    glm::vec3 scale;
    glm::mat4 model;

    glm::vec4 color;
};

#endif