#ifndef GRAPHICS_GAMEOBJECT_H_
#define GRAPHICS_GAMEOBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Texture.h"
#include "Shader.h"

class GameObject
{
public:
    GameObject(){};
    ~GameObject(){};
    virtual void loadTexture(const std::string &texturePath, const std::string &typeTexture);
    virtual void setVertices() = 0;
    virtual void setupBufferVertex() = 0;
    virtual void draw(Shader &shader) = 0;
    virtual void setColor(float red, GLfloat green, GLfloat blue) = 0;
    virtual GLuint getVAO();
    virtual GLuint getVBO();
protected:
    Texture *texture;
    GLuint VAO,VBO;
};

#endif