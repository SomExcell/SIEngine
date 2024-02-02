#ifndef WINDOW_CAMERA_H_
#define WINDOW_CAMERA_H_

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 position, float fov);

    void rotate(float x, float y, float z);
    void move();
    void setPosition(glm::vec3 position);
    void setFront(glm::vec3 front);

    glm::mat4 getProjection();
    glm::mat4 getView();
public:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 position;

    glm::mat4 rotation;

    float fov;
    float speed = 5;
    float camX = 0.0f;
    float camY = 0.0f;
    float lastTime;
    float currentTime;
    float delta = 5;

private:
    void updateVectors();

};

#endif