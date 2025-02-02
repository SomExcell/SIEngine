#ifndef LIGHTING_DIRECTION_LIGHT_H_
#define LIGHTING_DIRECTION_LIGHT_H_

#include "Light.h"

class DirectionLight : public Light
{
public:
    DirectionLight();
    ~DirectionLight(){};

    void draw() override;

private:

};

#endif