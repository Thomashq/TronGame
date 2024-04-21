#pragma once
#include "Globals.h"
#include "Platform.h"
#include "World.h"
#include "Camera.h"

enum class TronState
{
    GameLoop,
    Menu,
    Exit
};

class TronEngine
{
public:
    Platform *platform;
    TronState currentState;

    TronEngine(Platform *platform);
    ~TronEngine();

    void Init();

    void Run();

    void Stop();

private:
    void Render();

    World *world;
    Camera *camera;
};
