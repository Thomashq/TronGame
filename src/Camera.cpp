#include "Camera.h"
#include "Globals.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::Draw(Shader &shader)
{
    glm::mat4 view = this->GetViewMatrix();

    shader.Use();
    shader.SetMatrix4f("view", view);
}

void Camera::ProcessKeyboard(Movement direction)
{
    double velocity = (double)this->MovementSpeed * Globals::deltaTime;
    std::cout << "MOVING at speed " << Globals::deltaTime << std::endl;
    
    if(direction == Movement::FORWARD)
        this->Position += this->Front * (float)velocity;
    if(direction == Movement::BACKWARD)
        this->Position -= this->Front * (float)velocity;    
    if(direction == Movement::LEFT)
        this->Position -= this->Right * (float)velocity;
    if(direction == Movement::RIGHT)
        this->Position += this->Right * (float)velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw += xoffset;
    this->Pitch += yoffset;

    if(this->Pitch > 89.0f)
        this->Pitch = 89.0f;
    if(this->Pitch < -89.0f)
        this->Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);

    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}