#ifndef WINDOW_CAMERA_H_
#define WINDOW_CAMERA_H_

#include "glm/glm.hpp"

class Camera
{
public:
    Camera(const glm::vec3 &position, const float &fov);

    void Rotate(const float &x, const float &y, const float &z);
    void Move();
    void SetPosition(glm::vec3 position);
    void SetFront(glm::vec3 front);

    glm::mat4 GetProjection();
    glm::mat4 GetView();

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
    void UpdateVectors();

};

#endif