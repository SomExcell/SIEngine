#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 1.0f;
const GLfloat SPEED = 10.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

    glm::mat4 GetViewMatrix();

    void ProcessKeyBoard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);

    GLfloat getZoom();
private:
    void updateCameraVectors();

    glm::vec3 Position;
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat movementSpeed = SPEED;
    GLfloat mouseSensitivity = SENSITIVITY;
    GLfloat zoom = ZOOM;
};

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX,upY,upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position,Position + Front, Up);
}

void Camera::ProcessKeyBoard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = movementSpeed * deltaTime;
    if(direction == FORWARD){Position += Front * velocity;}
    if(direction == BACKWARD){Position -= Front * velocity;}
    if(direction == LEFT){Position -= Right * velocity;}
    if(direction == RIGHT){Position += Right * velocity;}
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;
    
    if(constrainPitch)
    {
        if(Pitch > 80.0f){Pitch = 80.0f;}
        if(Pitch < -80.0f){Pitch = -80.0f;}
    }
    
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw) * cos(glm::radians(Pitch)));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw) * cos(glm::radians(Pitch)));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

    //std::cout << Position.x << '\n' << Position.y << '\n' << Position.z;
}

GLfloat Camera::getZoom()
{
    return zoom;
}
