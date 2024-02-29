#include <iostream>

#include "includes.h"


int main(int, char**){
    windowInit();

    GLFWwindow* window {createWindow()};
    if (window == nullptr) return -1;
    else glfwMakeContextCurrent(window);

    // GLAD manages function pointers for OpenGL so initialize GLAD before any OpenGL function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Tell OpenGL the size of the rendering window so OpenGL knows how to display the data and coordinates
    // It's actually okay to make it smaller than the window size, then the OpenGL rendering will be displayed
    // in a smaller window
    glViewport(0, 0, WIDTH, HEIGHT);
    // (-0.5 , 0.5) -> (400 , 300)

    // register callback function for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    Renderer<float> renderer {};
    renderer.useShaderProgram(); // shader program in use

    // renderer.sample_triangle();
    renderer.sample_rectangle();


    // Simple render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        renderer.glSettings({0.2f, 0.2f, 0.2f, 1.0f});
        // Rendering Commands
        renderer.render(Renderer<float>::DrawMode::DRAWELEMENTS);
         
        renderLoop(window);
    }

    renderer.release_memory();

    glfwTerminate();
    return 0;
}

