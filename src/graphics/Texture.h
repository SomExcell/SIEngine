#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

#include <iostream>
#include <string>

enum TextureType
{
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT,
};

class Texture {
public:
	Texture(){};
	Texture(const std::string &path);
	Texture(const unsigned int &id, const std::string &path, const TextureType &type);
	~Texture();

	Texture(const Texture& rhs);
	Texture(Texture&& rhs);

	Texture& operator=(const Texture& rhs);
	Texture& operator=(Texture&& rhs);
	
public:
	void bind();
	void loadTexture(const std::string &path);
	std::string findNameFile(const std::string &path);

	unsigned int getID();
	int getWidth();
	int getHeight();
	TextureType getType();
	std::string getPath();
	std::string getNameFile();

	void setType(const TextureType &type);

private:
	unsigned int id;
	int width;
	int height;
	std::string path;
	std::string nameFile;
	TextureType type;
};

extern Texture* load_texture(const std::string &filename);

#endif 