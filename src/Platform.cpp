#include "Platform.h"

#include <iostream>

namespace
{
    bool isRunning = false;

    void framebufferSizeCB(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}

Platform::Platform(int Width, int Height, const char* Title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    this->Width = Width;
    this->Height = Height;
    this->Title = Title;
}

Platform::~Platform()
{
    glfwTerminate();
}

bool Platform::Init()
{
    this->window = glfwCreateWindow(this->Width, this->Height, this->Title, NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

    glViewport(0, 0, this->Width, this->Height);

    // Setting the proper callbacks
    glfwSetFramebufferSizeCallback(this->window, framebufferSizeCB);

    isRunning = true;
    return true;
}

void Platform::ProcessInput()
{
    glfwPollEvents();

	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		this->Stop();
}

void Platform::Update()
{

    // keep at the end of the method and while loop.
    // This switches the current buffer from the one we've been working on in the current frame
    glfwSwapBuffers(this->window);
}

bool Platform::WindowIsRunning()
{
    return isRunning;
}

void Platform::Stop()
{
    isRunning = false;
}

