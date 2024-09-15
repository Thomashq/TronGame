#include "Entity.h"

Entity::Entity(std::string path)
{
    this->model = new Model(path.c_str());
}

void Entity::Draw(Shader &shader)
{
    shader.Use();
    shader.SetMatrix4f("transform", this->transform);

    this->model->Draw(shader);
}
