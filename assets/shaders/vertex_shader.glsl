#version 330 core

layout (location = 0) in vec3 aPos; // A posi��o do v�rtice (passado pelo VBO)

uniform mat4 model;       // Matriz de modelo
uniform mat4 view;        // Matriz de vis�o
uniform mat4 projection;  // Matriz de proje��o

void main()
{
    // Multiplica as matrizes para transformar os v�rtices no espa�o da tela
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
