#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader & Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char *vertexPath, const char *fragmentPath)
{
    std::fstream shaderFile;

    shaderFile.open(vertexPath, std::fstream::in);
    if(shaderFile.fail())
        std::cout << "Vertex File Path: " << vertexPath << " failed to open." << std::endl;
    
    std::stringstream vertexStream;
    vertexStream << shaderFile.rdbuf();
    std::string vertexStr = vertexStream.str();
    const char* vertexSource = vertexStr.c_str();
    shaderFile.close();
   
    shaderFile.open(fragmentPath, std::fstream::in);
    if(shaderFile.fail())
        std::cout << "Fragment File Path: " << fragmentPath << " failed to open." << std::endl;
    
    std::stringstream fragmentStream;
    fragmentStream << shaderFile.rdbuf();
    std::string fragmentStr = fragmentStream.str();
    const char* fragmentSource = fragmentStr.c_str();
    shaderFile.close();

    unsigned int shaderVertex, shaderFragment;

    shaderVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVertex, 1, &vertexSource, NULL);
    glCompileShader(shaderVertex);
    checkCompileErrors(shaderVertex, "VERTEX");
    
    shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragment, 1, &fragmentSource, NULL);
    glCompileShader(shaderFragment);
    checkCompileErrors(shaderFragment, "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, shaderVertex);
    glAttachShader(this->ID, shaderFragment);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    glDeleteShader(shaderVertex);
    glDeleteShader(shaderFragment);
}

void Shader::SetFloat(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const char *name, float x, float y)
{
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const char *name, glm::vec2 &value)
{
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const char *name, glm::vec3 &value)
{
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const char *name, glm::vec4 &value)
{
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4f(const char *name, glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
