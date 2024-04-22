#ifndef LIGHTING_POINTLIGHT_H_
#define LIGHTING_POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();
    ~PointLight(){};

    void draw() override;
    void setColor(const glm::vec4 &color) override;

private:
    static int countLights;
    int indexLight;
    std::string indexLightStr;
};

#endif