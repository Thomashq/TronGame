#version 330 core

layout (location = 0) in vec3 aPos; // A posição do vértice (passado pelo VBO)

uniform mat4 model;       // Matriz de modelo
uniform mat4 view;        // Matriz de visão
uniform mat4 projection;  // Matriz de projeção

void main()
{
    // Multiplica as matrizes para transformar os vértices no espaço da tela
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
