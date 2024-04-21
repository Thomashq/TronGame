#include "Globals.h"

double Globals::internal::lastFrame = 0.0f;

double Globals::deltaTime = 0.0f;

void Globals::SetDeltaTime(double currentFrame)
{
    deltaTime = currentFrame - internal::lastFrame;
    internal::lastFrame = currentFrame;
}