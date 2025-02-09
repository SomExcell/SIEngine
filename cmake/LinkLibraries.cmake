set(SAVED_CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(SAVED_CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

add_subdirectory(libraries/assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)

add_subdirectory(libraries/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(libraries/glad/)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

add_subdirectory(libraries/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

add_subdirectory(libraries/spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

include_directories(libraries/stb_image)

set(CMAKE_CXX_FLAGS ${SAVED_CMAKE_CXX_FLAGS})
set(CMAKE_C_FLAGS ${SAVED_CMAKE_C_FLAGS})