include_directories("src/")
include_directories("game/")

add_executable(${PROJECT_NAME}
        src/SIEngine/Application.h
        src/SIEngine/Application.cpp

        src/SIEngine/EntryPoint.h

        game/GameApplication.cpp

        src/SIEngine.h
)