#ifndef SIENGINE_APPLICATION_H
#define SIENGINE_APPLICATION_H

namespace SIEngine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void Run() final;
    };

    Application* CreateApplication();
}

#endif //SIENGINE_APPLICATION_H
