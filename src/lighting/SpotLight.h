#ifndef LIGHTING_SPOTLIGHT_H_
#define LIGHTING_SPOTLIGHT_H_

#include "Light.h"

class SpotLight : public Light
{
public:
    SpotLight();
    ~SpotLight(){};

    void draw() override;

private:
    static int countLights;
    int indexLight;
    std::string indexLightStr;
};

#endif