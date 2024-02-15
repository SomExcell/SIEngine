#include "Texture.h"
#include <glad/glad.h>

Texture::Texture(const unsigned int &id, const int &width, const int &height) : id(id), width(width), height(height) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::bind(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int Texture::getID()
{
	return id;
}