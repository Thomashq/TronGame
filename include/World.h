#pragma once 
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Shader.h"

class World
{
public:
    World(float fov, float aspect, float zNear, float zFar);

    void Draw(Shader & shader);

private:
    glm::mat4 projection = glm::mat4(1.0f);
};