#include "Texture.h"
#include <glad/glad.h>
#include "stb_image.h"

Texture::Texture(const unsigned int &id, const std::string &path, const TextureType &type) : id(id), path(path),type(type) {}

Texture::Texture(const std::string &path)
{
	loadTexture(path);
}

Texture::~Texture() {
	//glDeleteTextures(1, &id);
}


Texture::Texture(const Texture& rhs):id(rhs.id),width(rhs.width),height(rhs.height),path(rhs.path),type(rhs.type),nameFile(rhs.nameFile){}

Texture::Texture(Texture&& rhs):id(rhs.id),width(rhs.width),height(rhs.height),path(rhs.path),type(rhs.type),nameFile(rhs.nameFile)
{
	rhs.id = 0;
	rhs.path = "";
	rhs.nameFile = "";
}

Texture& Texture::operator=(const Texture& rhs)
{
	id = rhs.id;
	width = rhs.height;
	height = rhs.height;
	path = rhs.path;
	type = rhs.type;
	nameFile = rhs.nameFile;
	return *this;
}

Texture& Texture::operator=(Texture&& rhs)
{
	id = rhs.id;
	width = rhs.height;
	height = rhs.height;
	path = rhs.path;
	type = rhs.type;
	nameFile = rhs.nameFile;
	rhs.id = 0;
	rhs.path = "";
	return *this;
}


void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::loadTexture(const std::string &path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
	this->path = path;
	this->nameFile = findNameFile(path);
    id = textureID;
}

std::string Texture::findNameFile(const std::string &path)
{
	int stopIndex;
	std::string nameFile;
	for (size_t i = path.size() - 1; i >= 0; i--)
	{
		if(path[i] == '/'){stopIndex = i + 1;break;}
	}
	nameFile.resize(path.size() - stopIndex);
	for (size_t i = stopIndex,j = 0; i < path.size(); i++,j++)
	{
		nameFile[j] = path[i];
	}
	return nameFile;
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

std::string Texture::getNameFile()
{
	return nameFile;
}

void Texture::setType(const TextureType &type)
{
	this->type = type;
}
