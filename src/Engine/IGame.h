#ifndef SIENGINE_IGAME_H
#define SIENGINE_IGAME_H

#include <iostream>

class IGame
{
public:
    virtual ~IGame() = default;
protected:
    IGame() = default;

public:
    virtual void Create() = 0;
    virtual void Update() = 0;
};

#endif //SIENGINE_IGAME_H
