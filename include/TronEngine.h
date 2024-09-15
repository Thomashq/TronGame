#ifndef TRON_ENGINE_H
#define TRON_ENGINE_H

#include "Arena.h"
#include "Moto.h"
#include <vector>

class TronEngine {
public:
    TronEngine();
    ~TronEngine();

    void Init();
    void Run();

private:
    Arena* arena;
    std::vector<Moto*> motos;

    void Update(float deltaTime);
    void Render();

    GLuint shaderProgram;
};

#endif 
