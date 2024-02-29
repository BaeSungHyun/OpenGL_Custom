#ifndef CALLBACK_FUNC_H
#define CALLBACK_FUNC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// callback function for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// input function
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
}

#endif