#ifndef ARENA_H
#define ARENA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Arena {
public:
    Arena();
    ~Arena();

    void Init();
    void Render(GLuint gluint);

private:
    GLuint arenaVAO, arenaVBO;
    glm::mat4 model;
    float arenaVertices[12] = {
        -10.0f, 0.0f, -10.0f,  // canto inferior esquerdo
        10.0f, 0.0f, -10.0f,   // canto inferior direito
        -10.0f, 0.0f, 10.0f,   // canto superior esquerdo
        10.0f, 0.0f, 10.0f     // canto superior direito
    };
};

#endif // ARENA_H
