#include "Render.h"

void Render::RenderObjects()
{
    for(auto object : Objects)
    {
        object.draw();
    }
}

void Render::AddObject(const GameObject &gameObject)
{
    Objects.push_back(gameObject);
}

std::vector<GameObject> Render::Objects = {};
