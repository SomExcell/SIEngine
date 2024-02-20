#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

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
	Texture(const unsigned int &id, const std::string &path, const TextureType &type);
	~Texture();

	Texture(const Texture& rhs);
	Texture(Texture&& rhs);

	Texture& operator=(const Texture& rhs);
	Texture& operator=(Texture&& rhs);
	
public:
	void bind();
	unsigned int getID();
	int getWidth();
	int getHeight();
	TextureType getType();
	std::string getPath();

	void setType(TextureType type);
	void setID(unsigned int);
	void setPath(std::string path);

private:
	unsigned int id;
	int width;
	int height;
	std::string path;
	TextureType type;
};

extern Texture* load_texture(const std::string &filename);

#endif 