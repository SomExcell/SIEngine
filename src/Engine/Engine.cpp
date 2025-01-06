#include "Engine.h"

void Engine::Run(std::unique_ptr<IGame> game)
{
    game->Create();
    game->Update();
}
