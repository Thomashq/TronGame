#include "Moto.h"
#include <glm/gtc/type_ptr.hpp>

// Construtor
Moto::Moto(glm::vec3 initialPosition, glm::vec3 motoColor)
    : position(initialPosition), color(motoColor), speed(5.0f), maxSpeed(15.0f), minSpeed(2.0f)
{
    direction = glm::vec3(1.0f, 0.0f, 0.0f);  // Direção inicial (frente)
    model = glm::mat4(1.0f);  // Matriz de modelo inicial
}

// Destrutor
Moto::~Moto() {
    glDeleteVertexArrays(1, &motoVAO);
    glDeleteBuffers(1, &motoVBO);
}

// Função que configura os VBOs e VAOs da moto
void Moto::setupMoto() {
    glGenVertexArrays(1, &motoVAO);
    glGenBuffers(1, &motoVBO);

    glBindVertexArray(motoVAO);

    glBindBuffer(GL_ARRAY_BUFFER, motoVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(motoVertices), motoVertices, GL_STATIC_DRAW);

    // Posição dos vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Função que renderiza a moto
void Moto::renderMoto(GLuint shaderProgram) {
    // Define a matriz de modelo para a moto (transformações de posição e escala)
    model = glm::translate(glm::mat4(1.0f), position);

    // Passa a matriz de modelo para o shader
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Define a cor da moto
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));

    // Renderiza a moto
    glBindVertexArray(motoVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);  // Desenha a moto como um cubo
    glBindVertexArray(0);
}

// Função para mover a moto para frente
void Moto::moveForward(float deltaTime) {
    position += direction * speed * deltaTime;
}

// Função para mover a moto para a esquerda
void Moto::moveLeft(float deltaTime) {
    position -= glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * speed * deltaTime;
}

// Função para mover a moto para a direita
void Moto::moveRight(float deltaTime) {
    position += glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * speed * deltaTime;
}

// Função para aumentar a velocidade da moto
void Moto::accelerate() {
    if (speed < maxSpeed) {
        speed += 0.5f;
    }
}

// Função para diminuir a velocidade da moto
void Moto::decelerate() {
    if (speed > minSpeed) {
        speed -= 0.5f;
    }
}
