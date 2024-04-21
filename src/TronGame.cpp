#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#include "Platform.h"
#include "TronEngine.h"

int main()
{
	Platform *platform = new Platform(1280, 720, "TronGame btw");

	platform->Init();

	TronEngine *game = new TronEngine(platform);

	game->Init();
	game->Run();

	return 0;
}

