#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Model.h"
#include "Shader.h"

class Entity
{
public:
    
    Entity(std::string path);

    void Draw(Shader &shader);

private:
    Model *model;
    glm::mat4 transform = glm::mat4(1.0f);
};