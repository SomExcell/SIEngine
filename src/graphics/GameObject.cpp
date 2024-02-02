#include "GameObject.h"

void GameObject::loadTexture(const std::string &texturePath, const std::string &typeTexture)
{
    texture = load_texture(texturePath);
}

GLuint GameObject::getVAO()
{
    return VAO;
}

GLuint GameObject::getVBO()
{
    return VBO;
}
