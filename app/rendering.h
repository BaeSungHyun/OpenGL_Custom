#ifndef RENDERING_H
#define RENDERING_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "pre_rendering.h"

template <typename T>
class Renderer : public Pre_Rendering<T> {
public:
    Renderer() {};
    ~Renderer() {
    };

    void render() {
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->useShaderProgram();

        glBindVertexArray(this->VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    };
};

void renderTriangle(const unsigned int& shaderProgram, const unsigned int& VAO) {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3); // currently active shader, the previously defined vertex attribute configuration method and with the VBO's vertex data (indirectly bound via the VAO)
}

void renderRectangle(const unsigned int& shaderProgram, const unsigned int& VAO) {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    // Locating uniform variable does not require to use the shader program first.
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUseProgram(shaderProgram);
    // Updating a unifrom variable does require to first ue the program.
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // EBO
    // first param : mode
    // second param : vertices to draw
    // third param : indice type
    // fourth param : specify an offset in the EBO
    // glDrawElements takes its indices from the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER object.
    // We have to bind the corresponding EBO each time. VAO keeps the last EBO only.
}

#endif