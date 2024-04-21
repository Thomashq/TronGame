#pragma once 
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shader
{
public:
    unsigned int ID;

    Shader() {}

    Shader& Use();

    void Compile(const char* vertexPath, const char* fragmentPath);

    void SetFloat(const char* name, float value);
    void SetInteger(const char* name, int value);
    void SetVector2f(const char* name, float x, float y);
    void SetVector2f(const char* name, glm::vec2& value);
    void SetVector3f(const char* name, float x, float y, float z);
    void SetVector3f(const char* name, glm::vec3& value);
    void SetVector4f(const char* name, float x, float y, float z, float w);
    void SetVector4f(const char* name, glm::vec4& value);
    void SetMatrix4f(const char* name, glm::mat4& matrix);

private:
    void checkCompileErrors(unsigned int object, std::string type);
};