#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

#include <string>

class Texture {
public:
	Texture(const unsigned int &id, const int &width, const int &height);
	~Texture();

public:

	
public:
	void bind();
	unsigned int getID();
	int getWidth();
	int getHeight();

private:
	unsigned int id;
	int width;
	int height;
};

extern Texture* load_texture(const std::string &filename);

#endif 