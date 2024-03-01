#ifndef PRE_RENDERING_H
#define PRE_RENDERING_H

#include <iostream>
#include "shader.h"
#include "vertex.h"



// OpenGL Binding Object Class
template <typename T>
class Pre_Rendering {
public:
    Pre_Rendering();
    ~Pre_Rendering();

    void addVertices(const Vertices<T>& inputs);
    void useShaderProgram();

    void vectorToArray();

    void release_memory();

    // Samples
    void sample_triangle();
    void sample_rectangle();

protected:
    Shader shaderProgram;
    
    // UNIQUE FOR EACH VAO
    
    enum { VBO, EBO, OBJ_SIZE };
    
    unsigned int VAO;
    unsigned int gl_buffer_obj [ OBJ_SIZE ];
    // EBO Indices
    unsigned int* indices;

    // Vector of Vertex Array
    Vertices<T>* pVertices;
    unsigned int size_pVertices;

    // Vertex Array
    Vertex<T>* pVertexArray;

    // Total Number of Vertices
    int totalVertices;
};


// Implementation
template <typename T>
Pre_Rendering<T>::Pre_Rendering() : 
    shaderProgram("/home/baebae/Opengl/glsl/vertex.shader", "/home/baebae/Opengl/glsl/fragment.shader"),
    size_pVertices(1), indices (nullptr),
    VAO(0), totalVertices(0)
{
    pVertices = new Vertices<T> [size_pVertices];

    for (int i = 0; i < OBJ_SIZE; i++) {
        gl_buffer_obj[i] = 0;
    }
}

template <typename T>
Pre_Rendering<T>::~Pre_Rendering() {
    delete[] pVertices;
    pVertices = nullptr;
    pVertexArray = nullptr;
    delete[] indices;
    indices = nullptr;
}

template <typename T>
void Pre_Rendering<T>::vectorToArray() {
    // possible because vectors tore elements contiguously
    pVertexArray = &(pVertices[size_pVertices - 1].vecVertex[0]);
}

template <typename T>
void Pre_Rendering<T>::release_memory() {
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(OBJ_SIZE, gl_buffer_obj); // silently ignores 0's and names that do not correspond to existing buffer objects. 
    shaderProgram.deleteProgram();
}

template <typename T>
void Pre_Rendering<T>::addVertices(const Vertices<T>& inputs) {
    pVertices[size_pVertices - 1].addVertices(inputs);
    totalVertices += static_cast<int>(inputs.vecVertex.size());
}

template <typename T>
void Pre_Rendering<T>::useShaderProgram() {
    shaderProgram.use();
}

template <typename T>
void Pre_Rendering<T>::sample_triangle() {
    addVertices({
        {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
    });

    glGenBuffers(OBJ_SIZE - 1, gl_buffer_obj); // Doesn't need EBO

    vectorToArray();    

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<T>) * (pVertices[size_pVertices - 1].vecVertex.size()), 
                   pVertexArray , GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);

    // location = 0 : pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, pos));
    glEnableVertexAttribArray(0);

    // locatoni = 1 : color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, rgba));
    glEnableVertexAttribArray(1);
}


template <typename T>
void Pre_Rendering<T>::sample_rectangle() {
    addVertices({
        {0.5f, 0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {-0.5f, 0.5f, 0.0f}
    });

    // MODIFY IT !!!!
    if (indices == nullptr) {
        indices = new unsigned int[] {0, 1, 3, 1, 2, 3};
        totalVertices = 6;
    }

    glGenBuffers(OBJ_SIZE, gl_buffer_obj);

    vectorToArray();

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<T>) * (pVertices[size_pVertices - 1].vecVertex.size()),
                    pVertexArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_buffer_obj[EBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * totalVertices, indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_buffer_obj[EBO]);
    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);

    // location = 0 : pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, pos));
    glEnableVertexAttribArray(0);

    // location = 1 : color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, rgba));
    glEnableVertexAttribArray(1);    

}


#endif