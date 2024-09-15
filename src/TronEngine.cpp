#include "TronEngine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

TronEngine::TronEngine() : arena(nullptr), shaderProgram(0) {}

TronEngine::~TronEngine() {
    delete arena;
    for (Moto* moto : motos) {
        delete moto;
    }
}

void TronEngine::Init() {
    // Inicializa a arena
    arena = new Arena();
    arena->Init();

    // Inicializa as motos
    Moto* moto1 = new Moto(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Moto vermelha
    Moto* moto2 = new Moto(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));   // Moto azul
    moto1->setupMoto();
    moto2->setupMoto();
    motos.push_back(moto1);
    motos.push_back(moto2);

    // Carregar shaders (shaderProgram deve ser configurado aqui)
    // shaderProgram = LoadShaders(...);
}

void TronEngine::Run() {
    float deltaTime = 0.0f;
    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Atualiza o estado do jogo
        Update(deltaTime);

        // Renderiza o cenário
        Render();

        // Troca de buffers
        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
}

void TronEngine::Update(float deltaTime) {
    // Atualiza o movimento das motos (se necessário)
    for (Moto* moto : motos) {
        moto->moveForward(deltaTime);
    }
}

void TronEngine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Renderiza a arena
    arena->Render(shaderProgram);

    // Renderiza as motos
    for (Moto* moto : motos) {
        moto->renderMoto(shaderProgram);
    }
}
