include_directories("src/")

add_executable(${PROJECT_NAME}
        src/main.cpp

        src/window/Window.h
        src/window/Window.cpp

        src/window/Events.h
        src/window/Events.cpp

        src/window/Camera.h
        src/window/Camera.cpp

        src/graphics/Shader.h
        src/graphics/Shader.cpp

        src/graphics/Texture.h
        src/graphics/Texture.cpp

        src/graphics/GameObject.h
        src/graphics/GameObject.cpp

        src/graphics/Rectangle.h
        src/graphics/Rectangle.cpp

        src/graphics/Mesh.h
        src/graphics/Mesh.cpp

        src/graphics/Model.h
        src/graphics/Model.cpp

        src/loaders/png_loading.h
        src/loaders/png_loading.cpp

        src/lighting/Light.h
        src/lighting/Light.cpp

        src/lighting/DirectionLight.h
        src/lighting/DirectionLight.cpp

        src/lighting/PointLight.h
        src/lighting/PointLight.cpp

        src/lighting/SpotLight.h
        src/lighting/SpotLight.cpp

        src/graphics/stb_image.h

        src/Engine/Engine.h
        src/Engine/IGame.h

        src/Engine/Engine.cpp
        src/Game/Game.h
        src/Engine/Core/ConfigurationEngine.h
)