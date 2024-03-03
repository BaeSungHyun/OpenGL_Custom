#ifndef CALLBACK_FUNC_H
#define CALLBACK_FUNC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "init_functions.h"

float MOUSE_SENSITIVITY = 0.1f; // global variable
 
bool FRAMEBUFFER_RESIZE = false;
bool MOUSE_RBUTTON = false;
bool MOUSE_LBUTTON = false;
bool KEY_SHIFT = false;
bool KEY_CTRL = false;

bool B_POS = false; // if MOUSE POSITION changed
float XPOS = 0.0f;
float YPOS = 0.0f;

float LAST_XPOS = 0.0f;
float LAST_YPOS = 0.0f;

bool B_FOV = false; // if FOV is modified
float FOV = 45.0f; // default 45.0f -- controls zoom amount 

// callback function for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    FRAMEBUFFER_RESIZE = true;
    WIDTH = width;
    HEIGHT = height;
}

// input function
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
}

// callback function for tracing cursor movement
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    LAST_XPOS = XPOS;
    LAST_YPOS = YPOS;

    XPOS = (float)xpos;
    YPOS = (float)ypos;

    B_POS = true;
}

// callback function for tracing mouse click
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            switch (action) {
                case GLFW_PRESS: {
                    MOUSE_LBUTTON = true;
                    switch (mods) {
                        case GLFW_MOD_CONTROL: {
                            KEY_CTRL = true;
                            break;
                        }
                        case GLFW_MOD_SHIFT: {
                            KEY_SHIFT = true;
                            break;
                        }
                    }
                    break;
                }
                case GLFW_RELEASE: {
                    MOUSE_LBUTTON = false;
                    KEY_SHIFT = false;
                    KEY_CTRL = false;
                    break;
                }
            }
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            switch (action) {
                case GLFW_PRESS: {
                    MOUSE_RBUTTON = true;
                    switch (mods) {
                        case GLFW_MOD_CONTROL: {
                            KEY_CTRL = true;
                            break;
                        }
                        case GLFW_MOD_SHIFT: {
                            KEY_SHIFT = true;
                            break;
                        }
                    }
                    break;
                }
                case GLFW_RELEASE: {
                    MOUSE_RBUTTON = false;
                    KEY_SHIFT = false;
                    KEY_CTRL = false;
                    break;
                }
            }
            break;
        }
    }
}

// Callback function for scrolling
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // yoffset : amoung we scrolled vertically
    FOV -= (float)yoffset;
    if (FOV < 1.0f) 
        FOV = 1.0f;
    if (FOV > 45.0f)
        FOV = 45.0f; 

    B_FOV = true;
}

#endif