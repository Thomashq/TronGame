#include "Platform.h"
#include <iostream>

struct MouseOffset
{
    float xoffset;
    float yoffset;
} mouseOffset;

bool isRunning = false;
bool firstMouse = true;
bool mouseIsMoving = false;
float lastX = 0.0f;
float lastY = 0.0f;

void framebufferSizeCB(GLFWwindow* window, int width, int height);
void mouseCB(GLFWwindow *window, double xposIn, double yposIn);

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
    glfwSetCursorPosCallback(this->window, mouseCB);

    // tell GLFW to capture our mouse
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    isRunning = true;
    return true;
}

void Platform::ProcessInput(Camera &camera)
{
    glfwPollEvents();

	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		this->Stop();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Movement::FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Movement::BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Movement::LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Movement::RIGHT);

    if(mouseIsMoving)
    {
        camera.ProcessMouseMovement(mouseOffset.xoffset, mouseOffset.yoffset);
        mouseIsMoving = false;
    }
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

double Platform::GetTime()
{
    return glfwGetTime();
}

void Platform::Stop()
{
    isRunning = false;
}

void framebufferSizeCB(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouseCB(GLFWwindow *window, double xposIn, double yposIn)
{
    mouseIsMoving = true;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    mouseOffset.xoffset = xoffset;
    mouseOffset.yoffset = yoffset;
}