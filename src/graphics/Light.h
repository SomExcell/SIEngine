#ifndef GRAPHICS_LIGHT_H_
#define GRAPHICS_LIGHT_H_

#include "GameObject.h"

class Light : public GameObject
{
public:
    Light();
    ~Light();
    void setVertices() override;
    void setupBufferVertex() override;
    void draw() override;
    void setColor(GLfloat red, GLfloat green, GLfloat blue) override;
private:
    GLfloat vertices[288];
};

#endif