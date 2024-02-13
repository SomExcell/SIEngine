#ifndef GRAPHICS_RECTANGLE_H_
#define GRAPHICS_RECTANGLE_H_

#include "GameObject.h"

class Rectangle:public GameObject
{
public:
    Rectangle();
    ~Rectangle() override;
    void setVertices() override;
    void setupBufferVertex() override;
    void draw() override;
private:
    GLfloat vertices[288];
};

#endif