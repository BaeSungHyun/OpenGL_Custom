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

                int vertexColorLocation = this->shaderProgram.findUniformLocation("uniColor");
                this->shaderProgram.changeUniformFloat(vertexColorLocation, {0.0f, greenValue, 0.0f, 1.0f});
                glDrawElements(GL_TRIANGLES, this->totalVertices, GL_UNSIGNED_INT, 0); 
                break;
            }
        }
    };
};
#endif