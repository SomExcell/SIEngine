#ifndef GRAPHICS_GAME_OBJECT_H_
#define GRAPHICS_GAME_OBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#include "SIEngine/GraphicsAPI/OpenGL/Texture.h"
#include "SIEngine/GraphicsAPI/OpenGL/Shader.h"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void loadTexture(const std::string &texturePath);
    virtual void loadDiffuseMap(const std::string &texturePath);
    virtual void loadSpecularMap(const std::string &texturePath);
    virtual void loadEmissionMap(const std::string &texturePath);

    virtual void draw();
    virtual void setColor(const glm::vec4 &color);

    virtual void setPosition(const glm::vec3 &position);
    virtual void setScale(const glm::vec3 &scale);
    virtual void setModel(const glm::mat4 &model);
    virtual void setRotate(const float &angle, const glm::vec3 &rotate);

    virtual glm::vec3 getPosition();
    virtual glm::vec3 getScale();
    virtual glm::mat4 getModel();
    virtual glm::vec4 getColor();

    virtual GLuint getVAO();
    virtual GLuint getVBO();

    virtual void flipTexture(bool state);

public:
    bool outline = false;

protected:
    virtual void setVertices(){};
    virtual void setupBufferVertex(){};

protected:
    Texture* texture = nullptr;
    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
    Texture* emissionMap = nullptr;

    unsigned int VBO = 0, VAO = 0, EBO = 0;

    glm::vec3 position = glm::vec3(1.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotate = glm::vec3(1.0f);
    float angle = 0.0f;
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec4 color;

    bool _flipTexture = true;

};

#endif