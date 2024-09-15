#ifndef MOTO_H
#define MOTO_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Moto {
public:
    Moto(glm::vec3 initialPosition, glm::vec3 color);
    ~Moto();

    void setupMoto();
    void renderMoto(GLuint shaderProgram);

    void moveForward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void accelerate();
    void decelerate();

private:
    GLuint motoVAO, motoVBO;
    glm::mat4 model;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float speed;
    float maxSpeed;
    float minSpeed;

    float motoVertices[36] = {
        // Vértices da moto (exemplo de cubo)
        -0.5f, 0.0f, -0.5f,  // canto inferior esquerdo
        0.5f, 0.0f, -0.5f,   // canto inferior direito
        -0.5f, 1.0f, -0.5f,  // canto superior esquerdo
        0.5f, 1.0f, -0.5f,   // canto superior direito
        -0.5f, 0.0f, 0.5f,   // canto inferior esquerdo (parte de trás)
        0.5f, 0.0f, 0.5f,    // canto inferior direito (parte de trás)
        -0.5f, 1.0f, 0.5f,   // canto superior esquerdo (parte de trás)
        0.5f, 1.0f, 0.5f     // canto superior direito (parte de trás)
    };
};

#endif // MOTO_H
