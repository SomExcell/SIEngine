#include "Camera.h"
#include "window/Events.h"

#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

Camera::Camera(const glm::vec3 &position, const float &fov) : position(position), fov(fov), rotation(1.0f) {
	lastTime = glfwGetTime();
    UpdateVectors();
}

void Camera::UpdateVectors(){
	front = glm::vec3(rotation * glm::vec4(0,0,-1,1));
	right = glm::vec3(rotation * glm::vec4(1,0,0,1));
	up = glm::vec3(rotation * glm::vec4(0,1,0,1));
}

void Camera::Rotate(const float &x, const float &y, const float &z){
	rotation = glm::rotate(rotation, z, glm::vec3(0,0,1));
	rotation = glm::rotate(rotation, y, glm::vec3(0,1,0));
	rotation = glm::rotate(rotation, x, glm::vec3(1,0,0));

    UpdateVectors();
}

void Camera::Move()
{
	currentTime = glfwGetTime();
	delta = currentTime - lastTime;
	lastTime = currentTime;
	if (Events::pressed(GLFW_KEY_W)){
		position += front * delta * speed;
	}
	if (Events::pressed(GLFW_KEY_S)){
		position -= front * delta * speed;
	}
	if (Events::pressed(GLFW_KEY_D)){
		position += right * delta * speed;
	}
	if (Events::pressed(GLFW_KEY_A)){
		position -= right * delta * speed;
	}

	if (Events::_cursor_locked){
		camY += -Events::deltaY / Window::height * 2;
		camX += -Events::deltaX / Window::height * 2;

		if (camY < -glm::radians(89.0f)){
			camY = -glm::radians(89.0f);
		}
		if (camY > glm::radians(89.0f)){
			camY = glm::radians(89.0f);
		}

		rotation = glm::mat4(1.0f);
        Rotate(camY, camX, 0);
	}
}

glm::mat4 Camera::GetProjection(){
	float aspect = (float)Window::width / (float)Window::height;
	return glm::perspective(fov, aspect, 0.1f, 100.0f);
}

glm::mat4 Camera::GetView(){
	return glm::lookAt(position, position + front, up);
}