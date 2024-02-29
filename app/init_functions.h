#ifndef INIT_FUNCTIONS_H
#define INIT_FUNCTIONS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

void windowInit() {
    glfwInit();
    // glfwWindowHint :
    // first arg : what option to configure 
    // second arg : integer that sets the value of previous option 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Pointer is returned by value
GLFWwindow* createWindow() {
    // Create a window object
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learning", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    return window;
}

void renderLoop(GLFWwindow* window) {
    // Uses Double Buffer by default
    glfwSwapBuffers(window); // swap the color buffer that is used to render to during this render iteration
    glfwPollEvents(); // Checks if any events are triggered (mouse, keyboard), updates the window state
    // and calls the corresponding functions (which would be registered by callback methods)
}

#endif