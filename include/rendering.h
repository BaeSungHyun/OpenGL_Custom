#ifndef RENDERING_H
#define RENDERING_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "pre_rendering.h"
#include "glSpace.h"

// Object Role : Matrix Multplications OpenGL Space, Uniform variables, Lighting Calculation

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
                // Sample Control
                float timeValue = glfwGetTime();
                float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

                int vertexColorLocation = this->shaderProgram.findUniformLocation("uniColor");
                this->shaderProgram.changeUniformFloat(vertexColorLocation, {0.0f, greenValue, 0.0f, 1.0f});
                glDrawElements(GL_TRIANGLES, this->totalIndices, GL_UNSIGNED_INT, 0); 
                break;
            }
        }
    };

    void translateObjectMat(const glm::vec3& translation) {
        glSpace.translateObjectT(translation);
    }
    void rotateObjectMat(const float& angleDegrees, const glm::vec3& axis) {
        glSpace.rotateObjectRPost(angleDegrees, axis);
    }

    void translateViewMat(const glm::vec3& translation) {
        glSpace.translateViewT(translation);
    }
    void rotateViewMat(const float& angleDegrees, const glm::vec3& axis) {
        glSpace.rotateViewR(angleDegrees, axis);
    }
    void translateEyeMat(const glm::vec3& translation) {
        glSpace.translateEyeT(translation);
        glSpace.convertEyeToView();
    }
    void rotateEyeMat(const float& angleDegrees, const glm::vec3& axis) {
        glSpace.rotateEyeR(angleDegrees, axis);
        glSpace.convertEyeToView();
    }

    void rotateFirstEyeMat(const float& angleDegrees, const glm::vec3& axis) {
        glSpace.rotateFirstEyeR(angleDegrees, axis);
    }

    void rotateDepthCenterMat(const float& angleDegrees, const glm::vec3& axis) {
        glSpace.rotateDepthCenterR(angleDegrees, axis);
    }

    void setCamera(const glm::vec3& pos, const glm::vec3& tar) {
        glSpace.setCamPos(pos);
        glSpace.setCamTar(tar);
        glSpace.setCamAxes();

        glSpace.setViewTByCam(); // View & Eye (inverse relationship)
        glSpace.setViewRByCam(); // View & Eye (inverse relationship)
    } 

    void setDepthCenter(const float zMiddle) {
        glSpace.setDepthCenterT_z(zMiddle);
    }

    void setProjectionPerspective(const float& fovDegree, const float& width, 
            const float& height, const float& zNear, const float& zFar) {
        glSpace.perspective(fovDegree, width, height, zNear, zFar);
    }

    void setUniformObject() const {
        int objectLoc = this->shaderProgram.findUniformLocation("object");
        this->shaderProgram.changeUniformGlm(objectLoc, glm::value_ptr(glSpace.getObjectMatrix()));
    }
    // View & Eye
    void setUniformView() const {
        int viewLoc = this->shaderProgram.findUniformLocation("view");
        this->shaderProgram.changeUniformGlm(viewLoc, glm::value_ptr(glSpace.getViewMatrix()));
    }

    void setUniformFirstEyeR() const {
        int eyeRLoc = this->shaderProgram.findUniformLocation("eyeR");
        this->shaderProgram.changeUniformGlm(eyeRLoc, glm::value_ptr(glSpace.getFirstEyeRMatrix()));
    }

    void setUniformCenter() const {
        int centerLoc = this->shaderProgram.findUniformLocation("center");
        this->shaderProgram.changeUniformGlm(centerLoc, glm::value_ptr(glSpace.getCenterMatrix()));
    }

    void setUniformProjection() const {
        int projectionLoc = this->shaderProgram.findUniformLocation("projection");
        this->shaderProgram.changeUniformGlm(projectionLoc, glm::value_ptr(glSpace.getPerspective()));
    }

private:
    GlSpace glSpace;
};
#endif