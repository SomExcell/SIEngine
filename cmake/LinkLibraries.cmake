add_subdirectory(libraries/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(libraries/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(libraries/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(libraries/assimp)
target_link_libraries(${PROJECT_NAME} assimp)

include_directories(libraries/stb_image)