#ifndef WINDOW_H
#define WINDOW_H
#include "../out/build/x64-debug/_deps/glfw-src/include/GLFW/glfw3.h"

class Window {
public:
    // Construtor e Destrutor
    Window(int width, int height, const char* title);
    ~Window();

    // Métodos para manipular a janela
    bool shouldClose();
    void swapBuffers();
    void pollEvents();

    // Obtém as entradas de teclado
    static bool isKeyPressed(int key);

private:
    GLFWwindow* window;  // Ponteiro para a janela
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
