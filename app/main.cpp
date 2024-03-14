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
    glfwSetScrollCallback(window, scroll_callback);

    Renderer<float> renderer {}; // Global Variable

    // Renderer as global variable    
    renderer.useShaderProgram(); // shader program in use

    renderer.setProjectionPerspective(45.0f, WIDTH, HEIGHT, NEAR, FAR);
    renderer.setCamera(glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // cameraPos, targetPos
    renderer.setDepthCenter((NEAR + FAR) / 2);

    // Light
    renderer.setAmbient(0.5f, 0.5f, 0.5f); // Red Ambient Light
    renderer.setDiffuse(glm::vec3(0.4f, 0.0f, 0.0f));
    renderer.setLightPos(glm::vec3(0.0f, 100.0f, 100.0f));

    renderer.setUniformObject();
    renderer.setUniformView();
    renderer.setUniformFirstEyeR();
    renderer.setUniformProjection();
    renderer.setUniformCenter();
    renderer.setTextureUnit();
    renderer.setUniformLight();

    // SAMPLES
    // renderer.sample_triangle();
    // renderer.sample_rectangle();
    renderer.sample_texture_rectangle();

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        renderer.glSettings({0.2f, 0.2f, 0.2f, 1.0f});

        if (FRAMEBUFFER_RESIZE) {
            renderer.setProjectionPerspective(45.0f, WIDTH, HEIGHT, NEAR, FAR);
            renderer.setUniformProjection();
            FRAMEBUFFER_RESIZE = false;
        }
        
        if (MOUSE_RBUTTON && B_POS) {        
            float xOffset = XPOS - LAST_XPOS;
            float yOffset = LAST_YPOS - YPOS; // OpenGL Coordinate and Window y-axis is reversed

            xOffset *= MOUSE_SENSITIVITY;
            yOffset *= MOUSE_SENSITIVITY;

            glm::vec3 tempAxis = glm::vec3(yOffset , -xOffset, 0);
            if (tempAxis[1] < 0) 
                tempAxis = -tempAxis;
            float offset = xOffset * xOffset + yOffset * yOffset;

            if (LAST_XPOS < XPOS) offset *= -1;

            if (KEY_SHIFT) {
                // World (Object) Rotation
                // renderer.rotateObjectMat(offset, -tempAxis); // minus Axis
                // renderer.setUniformCenter();
                renderer.rotateDepthCenterMat(offset, -tempAxis);
                renderer.setUniformCenter();
            } else if (KEY_CTRL) {
                // Eye Translation
                renderer.translateEyeMat(glm::vec3(xOffset, yOffset, 0.0f));
                renderer.setUniformView();
            } else {
                // Eye Rotation
                renderer.rotateFirstEyeMat( offset, tempAxis); // plus Axis
                renderer.setUniformFirstEyeR();
            }

            B_POS = false;
        }

        if (B_FOV) {
            renderer.setProjectionPerspective(FOV, WIDTH, HEIGHT,0.1f, 100.0f);
            renderer.setUniformProjection();
            B_POS = false;
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

