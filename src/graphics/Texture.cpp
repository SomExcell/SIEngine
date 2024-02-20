#include "Texture.h"
#include <glad/glad.h>

Texture::Texture(const unsigned int &id, const std::string &path, const TextureType &type) : id(id), path(path),type(type) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}


Texture::Texture(const Texture& rhs):id(rhs.id),width(rhs.width),height(rhs.height){}

Texture::Texture(Texture&& rhs):id(rhs.id),width(rhs.width),height(rhs.height),path(rhs.path),type(rhs.type)
{
	rhs.id = 0;
	rhs.path = "";
}

Texture& Texture::operator=(const Texture& rhs)
{
	id = rhs.id;
	width = rhs.height;
	height = rhs.height;
	path = rhs.path;
	type = rhs.type;
	return *this;
}

Texture& Texture::operator=(Texture&& rhs)
{
	id = rhs.id;
	width = rhs.height;
	height = rhs.height;
	path = rhs.path;
	type = rhs.type;
	rhs.id = 0;
	rhs.path = "";
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

TextureType Texture::getType()
{
	return type;
}

std::string Texture::getPath()
{
	return path;
}

void Texture::setType(TextureType type)
{
	this->type = type;
}

void Texture::setID(unsigned int id)
{
	this->id = id;
}

void Texture::setPath(std::string path)
{
	this->path = path;
}