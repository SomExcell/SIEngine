cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(PROJECT_NAME SIEngine)
project(${PROJECT_NAME})

include_directories("header/")
include_directories("src/")

add_executable(${PROJECT_NAME} src/main.cpp
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

						src/loaders/png_loading.h
						src/loaders/png_loading.cpp
						
						src/graphics/stb_image.h
						)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)