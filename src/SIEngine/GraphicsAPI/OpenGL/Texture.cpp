#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string &texturePath)
{
    this->fileName = GetNameFile(texturePath);
    LoadTexture(texturePath);
}

Texture::~Texture() = default;

Texture::Texture(const Texture& rhs) = default;

Texture::Texture(Texture&& rhs) noexcept = default;

Texture& Texture::operator=(const Texture& rhs) = default;

Texture& Texture::operator=(Texture&& rhs) noexcept = default;

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::LoadTexture(const std::string &texturePath)
{
    int channelsInFile;
    auto *data = stbi_load(texturePath.c_str(), &width, &height, &channelsInFile, 0);

    if (data)
    {
        Configure(channelsInFile, data);
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << texturePath << std::endl;
    }

    stbi_image_free(data);
}

void Texture::Configure(int channelsInFile, unsigned char* data)
{
    GLint format = 0;
    if (channelsInFile == 1)
        format = GL_RED;
    else if (channelsInFile == 3)
        format = GL_RGB;
    else if (channelsInFile == 4)
        format = GL_RGBA;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

std::string Texture::GetNameFile(const std::string &texturePath)
{
	size_t startIndex = 0;
	for (size_t i = texturePath.size() - 1; i > 0; i--)
	{
		if(texturePath[i] == '/')
        {
            startIndex = i + 1;
            break;
        }
	}

    return texturePath.substr(startIndex, texturePath.size() - startIndex);
}

unsigned int Texture::GetId() const
{
	return id;
}

int Texture::GetHeight() const
{
	return height;
}

int Texture::GetWidth() const
{
	return width;
}

TextureType Texture::GetType()
{
	return type;
}

std::string Texture::GetFileName()
{
	return fileName;
}

void Texture::SetType(const TextureType &textureType)
{
	this->type = textureType;
}
