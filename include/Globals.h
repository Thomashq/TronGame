#pragma once
#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>

#include "Entity.h"
#include "Shader.h"

namespace Globals
{
    namespace internal
    {
        extern double lastFrame;
    }

    template<class T, class ...Args> using Func = std::function<T(Args...)>;

    extern double deltaTime;

    static std::unordered_map<std::string, Entity*> entities;

    static std::unordered_map<std::string, Shader*> shaders;

    void SetDeltaTime(double currentFrame);
}