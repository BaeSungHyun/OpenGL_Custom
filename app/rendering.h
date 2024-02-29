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
    ~Renderer() {};

    enum class DrawMode{
        DRAWARRAY,
        DRAWELEMENTS
    };

    void glSettings(const std::initializer_list<T>& rgba) {
        float temp[4] {};
        auto first = rgba.begin();
        for (int i{0}; first != rgba.end(); first++, i++) {
            temp[i] = *first; 
        }

        glClearColor(temp[0], temp[1], temp[2], temp[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void render(DrawMode mode) {
        glBindVertexArray(this->VAO);

        switch (mode) {
            case DrawMode::DRAWARRAY : {
                glDrawArrays(GL_TRIANGLES, 0, this->totalVertices);
                break;
            }
            case DrawMode::DRAWELEMENTS : {
                float timeValue = glfwGetTime();
                float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

                int vertexColorLocation = this->shaderProgram.findUniformLocation("ourColor");
                this->shaderProgram.changeUniformFloat(vertexColorLocation, {0.0f, greenValue, 0.0f, 1.0f});
                glDrawElements(GL_TRIANGLES, this->totalVertices, GL_UNSIGNED_INT, 0); 
                break;
            }
        }
    };

    
};

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