#pragma once
#include <functional>
#include <unordered_map>
#include <string>

#include "Entity.h"
#include "Shader.h"

namespace Globals
{
    namespace internal
    {
        static float lastFrame = 0.0f;
    }

    template<class T, class ...Args> using Func = std::function<T(Args...)>;

    static float deltaTime = 0.0f;

    static std::unordered_map<std::string, Entity*> entities;

    static std::unordered_map<std::string, Shader*> shaders;

    void SetDeltaTime(float currentFrame)
    {
        deltaTime = currentFrame - internal::lastFrame;
        internal::lastFrame = currentFrame;
    }
}