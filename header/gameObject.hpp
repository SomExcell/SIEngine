#pragma once

#include <shader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#include <iostream>

class GameObject
{
public:
    GameObject(){};
    ~GameObject(){};
    virtual void loadTexture(const std::string &texturePath, const std::string &typeTexture, Shader &shsader);
    virtual void setVertices(){};
    virtual void setupBufferVertex(){};
    virtual void draw(){};
    virtual void setColor(GLfloat red, GLfloat green, GLfloat blue){};
    virtual GLuint getVAO();
    virtual GLuint getVBO();
protected:
    GLuint texture[2];
    GLuint VAO,VBO;
    GLuint countTexture = 0;
};

void GameObject::loadTexture(const std::string &texturePath, const std::string &typeTexture, Shader &shader)
{
    glGenTextures(1,&texture[countTexture]);
    glBindTexture(GL_TEXTURE_2D,texture[countTexture]);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    GLint width,height,nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath.c_str(),&width,&height,&nrChannels,0);
    if(data)
    {
        if(typeTexture == "jpg")
        {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        }else if(typeTexture == "png")
        {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        countTexture++;
        if(countTexture == 1){shader.setInt("texture1",0);}
        else if(countTexture == 2){shader.setInt("texture2", 1);}
        shader.setInt("countTexture",countTexture);
    }else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

GLuint GameObject::getVAO()
{
    return VAO;
}

GLuint GameObject::getVBO()
{
    return VBO;
}