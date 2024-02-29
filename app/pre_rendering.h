#ifndef PRE_RENDERING_H
#define PRE_RENDERING_H

#include <initializer_list>
#include <vector>
#include <iostream>
#include "shader.h"

// Single Vertex 
template <typename T>
struct Vertex {
    T pos[3] {}; // default initialize to 0
    T rgba[4] {}; // default initialize to 0

    Vertex() = default;

    Vertex(std::initializer_list<T> init) {
        range_initialize(init.begin(), init.end());
    };

    // for vector push_back
    Vertex& operator=(const Vertex& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < 3; i++) pos[i] = other.pos[i];
        for (int i = 0; i < 4; i++) rgba[i] = other.rgba[i];

        return *this; // return reference to the current object
    }

private:
    template<typename InputIterator>
    void range_initialize(InputIterator first, InputIterator last) {
        try {
            int index{0};
            for (; first != last; first++) {
                if (index < 3) pos[index++] = *first;
                else if (index >= 3) rgba[index++ - 3] = *first;
            }
        } catch (const std::exception& e) {
            std::cout << "Caught an exception : " << e.what() << std::endl;
        }
    }
};

// Multiple Vertices
template <typename T>
struct Vertices {
public:
    // elements on the heap memory; vector on stack memory
    std::vector<Vertex<T>> vecVertex;

    Vertices(){
    };

    Vertices(std::initializer_list<Vertex<T>> init) {   
        range_initialize(init.begin(), init.end());
    };

    ~Vertices() {
    };

    void addVertices(const Vertices& input) {
        for (auto iterator = input.vecVertex.cbegin(); iterator != input.vecVertex.cend(); iterator++)
            vecVertex.push_back(*iterator);
    }

    void addVertex(const Vertex<T>& input) {
        vecVertex.push_back(input);
    }

private:
    template<typename InputIterator>
    void range_initialize(InputIterator first, InputIterator last) {
        try {
            for (; first != last; first++) {
                vecVertex.push_back(*first);
            }
        } catch (const std::exception& e) {
            std::cout << "Caught an exception : " << e.what() << std::endl;
        }
    }
};

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

    void sample_triangle();
protected:
    Shader shaderProgram;
    enum { VBO, EBO, OBJ_SIZE };
    unsigned int VAO;
    unsigned int gl_buffer_obj [ OBJ_SIZE ];

    Vertices<T>* pVertices;
    unsigned int size_pVertices;

    Vertex<T>* pVertexArray;
};


// Implementation
template <typename T>
Pre_Rendering<T>::Pre_Rendering() : 
    shaderProgram("/home/baebae/Opengl/glsl/vertex.shader", "/home/baebae/Opengl/glsl/fragment.shader"),
    size_pVertices(1),
    VAO(0)
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
void Pre_Rendering<T>::sample_triangle() {
    pVertices[size_pVertices - 1].addVertices({
        {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
    });

    glGenBuffers(OBJ_SIZE - 1, gl_buffer_obj);

    vectorToArray();    

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);
    unsigned int temp = sizeof(Vertex<T>) * static_cast<unsigned int>(pVertices[size_pVertices - 1].vecVertex.size());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<T>) * static_cast<unsigned int>(pVertices[size_pVertices - 1].vecVertex.size()), 
                   pVertexArray , GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);

    // location = 0 : pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<float>), (const void*)offsetof(Vertex<T>, pos));
    glEnableVertexAttribArray(0);

    // locatoni = 1 : color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<float>), (const void*)offsetof(Vertex<T>, rgba));
    glEnableVertexAttribArray(1);
}

template <typename T>
void Pre_Rendering<T>::addVertices(const Vertices<T>& inputs) {
    pVertices[size_pVertices - 1].addVertices(inputs);
}

template <typename T>
void Pre_Rendering<T>::useShaderProgram() {
    shaderProgram.use();
}

#endif