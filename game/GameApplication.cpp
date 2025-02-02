#include "SIEngine.h"

class GameApplication : public SIEngine::Application
{
public:
    GameApplication(){}
    ~GameApplication(){}
};

SIEngine::Application* SIEngine::CreateApplication()
{
    GameApplication gameApplication;
    return new GameApplication{};
}
