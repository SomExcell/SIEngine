#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

#include "glad/glad.h"
#include <iostream>
#include <string>

enum TextureType
{
    None,
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT,
};

class Texture {
public:
	explicit Texture(const std::string &texturePath);
	~Texture();

	Texture(const Texture& rhs);
    Texture& operator=(const Texture& rhs);

    Texture(Texture&& rhs) noexcept;
	Texture& operator=(Texture&& rhs) noexcept;

public:
	void Bind() const;
	void LoadTexture(const std::string &texturePath);
	static std::string GetNameFile(const std::string &texturePath);

	GLuint GetId() const;
	int GetWidth() const;
	int GetHeight() const;
	TextureType GetType();
	std::string GetFileName();
	void SetType(const TextureType &textureType);
    void Configure(int channelsInFile, unsigned char* data);

private:
    GLuint id = 0;
	int width = 0;
	int height = 0;
	std::string fileName;
	TextureType type = TextureType::None;
};

#endif 