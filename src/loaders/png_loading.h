#ifndef LOADERS_PNG_LOADING_H_
#define LOADERS_PNG_LOADING_H_

#include <string>

class Texture;

extern Texture* load_texture(const std::string &path);

#endif 