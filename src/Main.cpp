#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "TronEngine.h"

// Callback de redimensionamento de janela
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Inicializa a GLFW
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar a GLFW" << std::endl;
        return -1;
    }

    // Cria a janela
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Tron Game", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Callback de redimensionamento de janela
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializa o GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar o GLAD" << std::endl;
        return -1;
    }

    // Inicializa o motor do jogo
    TronEngine* game = new TronEngine();
    game->Init();
    game->Run();

    // Finaliza o jogo
    delete game;

    // Fecha a janela e finaliza a GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
