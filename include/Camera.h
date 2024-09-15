#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Shader.h"

enum class Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed = 2.5f;
    float MouseSensitivity = 0.1f;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    glm::mat4 GetViewMatrix();

    void Draw(Shader &shader);

    void ProcessKeyboard(Movement direction);

    void ProcessMouseMovement(float xoffset, float yoffset);

private:
    void updateCameraVectors();
};