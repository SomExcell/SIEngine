#ifndef SIENGINE_ENGINE_H
#define SIENGINE_ENGINE_H

#include "IGame.h"

namespace Engine
{
    void Run(std::unique_ptr<IGame> game);
}

#endif //SIENGINE_ENGINE_H
