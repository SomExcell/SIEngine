#pragma once

#include <gameObject.hpp>

#include <glad/glad.h>

#include <iostream>

class Rectangle:public GameObject
{
public:
    Rectangle();
    ~Rectangle(){};
    void setVertices() override;
    void setupBufferVertex() override;
    void draw() override;
    void setColor(GLfloat red, GLfloat green, GLfloat blue) override;
private:
    GLfloat vertices[288];
};

Rectangle::Rectangle()
{
    setVertices();
    setupBufferVertex();
}

void Rectangle::setVertices()
{
    GLfloat cube[288] = {
    //positions                 //color            //texture coords
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f, //1
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,      1.0f, 0.0f, //2
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f, //3   back side
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f, //4
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,      0.0f, 1.0f, //5
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f, //6

    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//7
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//8
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//9    front side
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//10
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//11
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//12

    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//13
    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//14
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//15   left side
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//16
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//17
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//18

     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//19
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//20
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//21
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//22   right side
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//23
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//24

    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//25
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//26
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//27   down
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//28
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//29
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//30

    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f,//31
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 1.0f,//32
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//33   top
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      1.0f, 0.0f,//34
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 0.0f,//35
    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,      0.0f, 1.0f};//36
    
    std::copy(std::begin(cube),std::end(cube),std::begin(vertices));
}

void Rectangle::setupBufferVertex()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Rectangle::draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,36);
}

void Rectangle::setColor(GLfloat red, GLfloat green, GLfloat blue)
{
    for (size_t i = 0; i < 36; i++)
    {
        vertices[i*8+3] = red;
        vertices[i*8+4] = green;
        vertices[i*8+5] = blue;
    } 
    setupBufferVertex();
}