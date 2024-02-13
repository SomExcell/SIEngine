#ifndef LIGHTING_POINTLIGHT_H_
#define LIGHTING_POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();
    ~PointLight(){};

    void draw() override;
    void disable() override;
    void activate() override;

    char count;

private:
    static int cLights;
    static std::string countLights;
    static bool isPointLight;
};

#endif