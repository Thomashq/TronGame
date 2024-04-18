#include "TronEngine.h"

TronEngine::TronEngine(Platform *platform)
{
    this->platform = platform;
}

void TronEngine::Run()
{
    while (this->platform->WindowIsRunning())
	{
		this->platform->ProcessInput();



		this->platform->Update();
	}

    delete this->platform;
}

void TronEngine::Init()
{
    this->currentState = TronState::GameLoop;

    // Will load Models, Shaders and whatever needs a file to read with ResourceManager
}

void TronEngine::Stop()
{
    this->currentState = TronState::Exit;
    
    // Dealocate all Models and Shaders

    this->platform->Stop();
}
