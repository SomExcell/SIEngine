#ifndef LIGHTING_DIRECTIONLIGHT_H_
#define LIGHTING_DIRECTIONLIGHT_H_

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