#ifndef SAMPLE_TRIANGLE_H
#define SAMPLE_TRIANGLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "read_shader.h"
#include <iostream>

void triangle(unsigned int& shaderProgram, unsigned int& VAO, unsigned int& VBO) {
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };

    ///////////////////// VAO /////////////////////
    // VAO : Vertex Array Object can be bound just like a vertex buffer object and any subsequent vertex attribute
    //      calls from that point on will be stored inside the VAO. 
    glGenVertexArrays(1, &VAO);

    // bind/configure the corresponding VBO and attribute pointers
    glBindVertexArray(VAO);



    ///////////////////// VBO /////////////////////
    glGenBuffers(1, &VBO);

    // OpenGL has many types of buffer objects and the buffer type of a vertex buffer object is
    // GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // From this point, any buffer calls made will be used to configure the currently bound buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // fourth parameter options : 
    // GL_STREAM_DRAW - the data is set only once and used by the GPU at most a few times
    // GL_STATIC_DRAW - the data is set only once and used many times
    // GL_DYNAMIC_DRAW - the data is changed a lot and used many times


    ///////////////////// Vertex Shader /////////////////////
    // Relative Path doesn't work why?
    const char* vertexShaderSource = readShader("/home/baebae/Opengl/glsl/vertex.shader");

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Checking for successful compilation of shader
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];  
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }


    ///////////////////// Fragment Shader /////////////////////
    const char* fragmentShaderSource = readShader("/home/baebae/Opengl/glsl/fragment.shader");
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Checking for successful compilation of shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];  
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }


    ///////////////////// Shader Program /////////////////////
    // Shader Program is the final linked version of multiple shaders combined.
    // To use the recently compiled shaders we have to 'link' them to a shader program object and then 
    // activate this shader program when rendering objects.
    // ERROR : input and ouput does not match previous and next shader
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // link attached shaders
    // Checking for successful Shader Program
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" <<
            infoLog << std::endl;
    }

    // Delete the shaders, because we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    ///////////////////// Linking Vertex Attributes /////////////////////
    // Vertex Shader makes it possible to specify any input in the form of vertex attributes and while this
    // allows for great flexibility. It is mandatory to manually specify what part of input data goes to which
    // vertex attribute in the vertex shader.
    // We have to specify how OpenGL should interpret the vertex data before rendering.

    // Each vertex attribute takes its data from memory managed by the VBO and which VBO it takes it s data from (multiple VBOs possible)
    // is determined by the VBO currently bound to GL_ARRAY_BUFFER.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // first param : which vertex attribute to configure. In vertex shader, (location = 0) for 'aPos' variable
    // second param : size of the vertex attribute. In vertex shader, vec3 means '3' values
    // third param : type of the data which is GL_FLOAT. In vertex shader, vec* in GLSL consists of floating point values
    // fourth param : data to be normalized. 
    // fifth param : stride. Space between consecutive vertex attributes
    // sixth param : offet of where the position dta begins in the buffer. void*
    glEnableVertexAttribArray(0); // enable the vertex attribute by passing 'location = 0' as its argument


    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
#endif

