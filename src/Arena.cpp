#include "Arena.h"
#include <glm/gtc/type_ptr.hpp>

// Construtor
Arena::Arena() {
    // Inicializa a matriz de modelo
    model = glm::mat4(1.0f);
}

// Destrutor
Arena::~Arena() {
    glDeleteVertexArrays(1, &arenaVAO);
    glDeleteBuffers(1, &arenaVBO);
}

// Função que configura os VBOs e VAOs da arena
void Arena::Init() {
    glGenVertexArrays(1, &arenaVAO);
    glGenBuffers(1, &arenaVBO);

    glBindVertexArray(arenaVAO);

    glBindBuffer(GL_ARRAY_BUFFER, arenaVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arenaVertices), arenaVertices, GL_STATIC_DRAW);

    // Posicionamento dos vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Função que renderiza a arena
void Arena::Render(GLuint shaderProgram) {
    // Define a matriz de transformação para a arena (escala)
    model = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 1.0f, 10.0f));

    // Passa a matriz para o shader
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Renderiza a arena
    glBindVertexArray(arenaVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
