#ifndef LIGHTING_LIGHT_H_
#define LIGHTING_LIGHT_H_

#include "graphics/GameObject.h"

class Light : public GameObject
{
public:
    Light();
    ~Light();
    void setVertices() override;
    void setupBufferVertex() override;
    void draw() = 0;

    virtual void setDirection(glm::vec3 directionLight);
    virtual void setAmbientLight(glm::vec3 ambientLight);
    virtual void setDiffuseLight(glm::vec3 diffuseLight);
    virtual void setSpecularLight(glm::vec3 specularLight);
    virtual void setLights(glm::vec3 ambientLight, glm::vec3 diffuseLight, glm::vec3 specularLight);

    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    virtual void setLightRange(float constant, float linear, float quadratic);

    void setcutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);

    virtual void disable() = 0;
    virtual void activate() = 0;

protected:
    GLfloat vertices[288];

    glm::vec3 direction{-0.2f,-1.0f,-0.3f};
    glm::vec3 ambient{0.5f,0.5f,0.5f};
    glm::vec3 diffuse{0.5f,0.5f,0.5f};
    glm::vec3 specular{0.5f,0.5f,0.5f};

    float constant = 1.0f;
    float linear = 0.5f;
    float quadratic = 0.5f;

    float cutOff = 0.1f;
    float outerCutOff = 0.1f;
};

#endif