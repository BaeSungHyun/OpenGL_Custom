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

    // Register Callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    Renderer<float> renderer {}; // Global Variable

    // Renderer as global variable    
    renderer.useShaderProgram(); // shader program in use

    renderer.rotateObjectMat(-55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    renderer.setProjectionPerspective(45.0f, WIDTH, HEIGHT, 0.1f, 100.0f);
    renderer.setCamera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // cameraPos, targetPos

    renderer.setUniformObject();
    renderer.setUniformView();
    renderer.setUniformProjection();

    // SAMPLES
    // renderer.sample_triangle();
    renderer.sample_rectangle();


    // Render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        renderer.glSettings({0.2f, 0.2f, 0.2f, 1.0f});

        if (FRAMEBUFFER_RESIZE) {
            renderer.setProjectionPerspective(45.0f, WIDTH, HEIGHT, 0.1f, 100.0f);
            renderer.setUniformProjection();
            FRAMEBUFFER_RESIZE = false;
        }

        // Rendering Commands
        // renderer.render(Renderer<float>::DrawMode::DRAWARRAY);
        renderer.render(Renderer<float>::DrawMode::DRAWELEMENTS);
         
        renderLoop(window);
    }

    renderer.release_memory();

    glfwTerminate();
    return 0;
}

