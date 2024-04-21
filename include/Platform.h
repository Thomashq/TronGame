// Manage: window creation | input triggering
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Platform
{
public:
    bool Keys[1024];
    bool KeysProcessed[1024];
    int Width, Height;
    const char *Title = nullptr;

    Platform(int Width, int Height, const char *Title);
    ~Platform();

    bool Init();

    void ProcessInput(Camera &camera);

    void Update();

    bool WindowIsRunning();

    double GetTime();

    void Stop();

private:
    GLFWwindow *window = nullptr;
    
};