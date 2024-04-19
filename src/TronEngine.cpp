#include <iostream>
#include "TronEngine.h"
#include "Globals.h"

TronEngine::TronEngine(Platform *platform)
{
    this->platform = platform;
}

void TronEngine::Run()
{
    while (this->platform->WindowIsRunning())
	{
        Globals::SetDeltaTime(this->platform->GetTime());
		this->platform->ProcessInput();

        this->Render();

		this->platform->Update();
	}

    delete this->platform;
}

void TronEngine::Init()
{
    this->currentState = TronState::GameLoop;

    // Will load Entities, Shaders and whatever needs a file to read with ResourceManager
    Globals::shaders.insert({"standard", new Shader()});
    Globals::shaders["standard"]->Compile("assets/shaders/default.vs", "assets/shaders/default.fs");



}

void TronEngine::Stop()
{
    this->currentState = TronState::Exit;
    
    // Dealocate all Models and Shaders

    this->platform->Stop();
}

void TronEngine::Render()
{

}