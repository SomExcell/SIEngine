#include "Texture.h"
#include <glad/glad.h>

Texture::Texture(const unsigned int &id, const int &width, const int &height) : id(id), width(width), height(height) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

Texture::Texture(const Texture& rhs):id(rhs.id),width(rhs.width),height(rhs.height){}

Texture::Texture(Texture&& rhs):id(rhs.id),width(rhs.width),height(rhs.height)
{
	rhs.id = 0;
}

Texture& Texture::operator=(const Texture& rhs)
{
	id = rhs.id;
	width = rhs.height;
	height = rhs.height;
	return *this;
}

Texture& Texture::operator=(Texture&& rhs)
{
	id = rhs.id;
	width = rhs.height;
	height = rhs.height;
	rhs.id = 0;
	return *this;
}

void Texture::bind(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int Texture::getID()
{
	return id;
}

int Texture::getHeight()
{
	return height;
}

int Texture::getWidth()
{
	return width;
}