#include "World.h"

World::World(float fov, float aspect, float zNear, float zFar)
{
    this->projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}

void World::Draw(Shader &shader)
{
    shader.Use();
    shader.SetMatrix4f("projection", this->projection);
}
