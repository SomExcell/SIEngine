#ifndef SIENGINE_ENTRY_POINT_H
#define SIENGINE_ENTRY_POINT_H

#include "Application.h"

extern SIEngine::Application* SIEngine::CreateApplication();

int main()
{
    auto x = SIEngine::CreateApplication();
    x->Run();
    delete x;
}

#endif //SIENGINE_ENTRY_POINT_H
