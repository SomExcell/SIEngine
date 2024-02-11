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
    GameObject(){};
    virtual ~GameObject();

    virtual void loadTexture(const std::string &texturePath);
    virtual void loadDiffuseMap(const std::string &texturePath);
    virtual void loadSpecularMap(const std::string &texturePath);
    virtual void loadEmissionMap(const std::string &texturePath);

    virtual void setVertices() = 0;
    virtual void setupBufferVertex() = 0;

    virtual void draw() = 0;
    virtual void setColor(GLfloat red, GLfloat green, GLfloat blue) = 0;
    virtual void setPosition(glm::vec3 position);

    virtual GLuint getVAO();
    virtual GLuint getVBO();
protected:
    Texture *texture;
    Texture *diffuseMap;
    Texture *specularMap;
    Texture *emissionMap;

    GLuint VAO,VBO;

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::mat4 model;
};

#endif