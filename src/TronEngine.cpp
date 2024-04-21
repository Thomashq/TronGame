#include "TronEngine.h"
#include <iostream>
#include "Model.h"
#include "Entity.h"

TronEngine::TronEngine(Platform *platform)
{
    this->platform = platform;
}

void TronEngine::Run()
{
    while (this->platform->WindowIsRunning())
	{
        Globals::SetDeltaTime(this->platform->GetTime());
		this->platform->ProcessInput(*this->camera);

        std::cout << "Testing  " << Globals::deltaTime << std::endl;
        this->Render();

		this->platform->Update();
	}

    delete this->platform;
}

void TronEngine::Init()
{
    this->currentState = TronState::GameLoop;

    this->world = new World(45.0f, (float)this->platform->Width/(float)this->platform->Height, 0.1f, 100.0f);
    
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    glEnable(GL_DEPTH_TEST);

    // Will load Entities, Shaders and whatever needs a file to read with ResourceManager
    Globals::shaders.insert({"standard", new Shader()});
    Globals::shaders["standard"]->Compile("assets/shaders/default.vs", "assets/shaders/default.fs");

    Globals::entities.insert({"tallBuilding", new Entity("assets/models/TallBuilding01/TallBuilding01.obj")});

}

void TronEngine::Stop()
{
    this->currentState = TronState::Exit;
    
    // Dealocate all Models and Shaders

    this->platform->Stop();
}

void TronEngine::Render()
{
    glClearColor(48.f/255.f, 70.f/255.f, 116.f/255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Globals::shaders["standard"]->Use();

    this->world->Draw(*Globals::shaders["standard"]);    
    this->camera->Draw(*Globals::shaders["standard"]);

    Globals::entities["tallBuilding"]->Draw(*Globals::shaders["standard"]);
}