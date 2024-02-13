#ifndef LIGHTING_SPOTLIGHT_H_
#define LIGHTING_SPOTLIGHT_H_

#include "Light.h"

class SpotLight : public Light
{
public:
    SpotLight();
    ~SpotLight(){};

    void draw() override;
    void disable() override;
    void activate() override;
};

#endif