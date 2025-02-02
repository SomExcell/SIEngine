#ifndef SIENGINE_RENDER_H
#define SIENGINE_RENDER_H

#include <vector>
#include "graphics/GameObject.h"

class Render
{
public:
    static void RenderObjects();
    static void AddObject(const GameObject &gameObject);

private:
    static std::vector<GameObject> Objects;
};

#endif //SIENGINE_RENDER_H
