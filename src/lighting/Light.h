#ifndef LIGHTING_LIGHT_H_
#define LIGHTING_LIGHT_H_

#include "graphics/GameObject.h"

class Light : public GameObject
{
public:
    Light();
    ~Light();
    void draw() = 0;

    virtual void setDirection(const glm::vec3 &directionLight);
    virtual void setAmbientLight(const glm::vec3 &ambientLight);
    virtual void setDiffuseLight(const glm::vec3 &diffuseLight);
    virtual void setSpecularLight(const glm::vec3 &specularLight);
    virtual void setLights(const glm::vec3 &ambientLight, const glm::vec3 &diffuseLight, const glm::vec3 &specularLight);

    virtual void setConstant(const float &constant);
    virtual void setLinear(const float &linear);
    virtual void setQuadratic(const float &quadratic);
    virtual void setLightRange(const float &constant, const float &linear, const float &quadratic);

    virtual void setcutOff(const float &cutOff);
    virtual void setOuterCutOff(const float &outerCutOff);

    virtual void disable() = 0;
    virtual void activate() = 0;

protected:
    void setVertices() override;
    void setupBufferVertex() override;

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