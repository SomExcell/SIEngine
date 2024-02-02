#ifndef GRAPHICS_RECTANGLE_H_
#define GRAPHICS_RECTANGLE_H_

#include "GameObject.h"

class Rectangle:public GameObject
{
public:
    Rectangle();
    ~Rectangle();
    void setVertices() override;
    void setupBufferVertex() override;
    void draw() override;
    void setColor(GLfloat red, GLfloat green, GLfloat blue) override;
private:
    GLfloat vertices[288];
};

#endif