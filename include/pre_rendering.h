#ifndef PRE_RENDERING_H
#define PRE_RENDERING_H

#include <iostream>
#include "shader.h"
#include "vertex.h"
#include "image_loader.h"
#include "glLight.h"

// Object Role : Add Vertex, Indice, Texture, Normals ShaderProgram


// OpenGL Binding Object Class
template <typename T>
class Pre_Rendering {
public:
    Pre_Rendering();
    ~Pre_Rendering();

    void addVertices(const Vertices<T>& inputs);
    void addIndices(const std::vector<unsigned int>&);

    void useShaderProgram();

    void vectorToArray();

    void release_memory();

    // Samples
    void sample_triangle();
    void sample_rectangle();
    void sample_texture_rectangle();

protected:
    // Shader
    Shader shaderProgram;
    // Image Loader (texture)
    Image_Loader imgLoader;

    // UNIQUE FOR EACH VAO
    enum { VBO, EBO, OBJ_SIZE };

    unsigned int texture; // texture is not Buffer Object
    
    unsigned int VAO;
    unsigned int gl_buffer_obj [ OBJ_SIZE ];
    // EBO Indices
    unsigned int* pIndices;
    std::vector<unsigned int> vecIndices;

    // Vector of Vertex Array
    Vertices<T>* pVertices;
    unsigned int size_pVertices;

    // Vertex Array
    Vertex<T>* pVertexArray;

    // Total Number of Vertices and Indices
    int totalVertices;
    int totalIndices;
};


// Implementation
template <typename T>
Pre_Rendering<T>::Pre_Rendering() : 
    shaderProgram("/home/baebae/Opengl/glsl/vertex.shader", "/home/baebae/Opengl/glsl/fragment.shader"),
    size_pVertices(1), pIndices (nullptr),
    VAO(0), totalVertices(0), totalIndices(0),
    imgLoader("/home/baebae/Opengl/wall.jpg", true) // flip vertical set to 'true'
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
    pIndices = nullptr;

    // Causes Segmentation Fault
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &(gl_buffer_obj[VBO]));
    // glDeleteBuffers(1, &(gl_buffer_obj[EBO]));
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
void Pre_Rendering<T>::addIndices(const std::vector<unsigned int>& indices) {
    totalIndices += static_cast<int>(indices.size());
    vecIndices.insert(vecIndices.end(), std::make_move_iterator(indices.begin()), 
            std::make_move_iterator(indices.end()));
    pIndices = &(vecIndices[0]);
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

    glGenBuffers(OBJ_SIZE - 1, gl_buffer_obj); // Doesn't need EBO and TXD

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

    // locatIon = 1 : color
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

    addIndices(std::vector<unsigned int> {0, 1, 3, 1, 2, 3});

    glGenBuffers(OBJ_SIZE, gl_buffer_obj); 

    vectorToArray();

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<T>) * (pVertices[size_pVertices - 1].vecVertex.size()),
                    pVertexArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_buffer_obj[EBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * totalIndices, (const void*)(pIndices), GL_STATIC_DRAW);

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

template<typename T>
void Pre_Rendering<T>::sample_texture_rectangle() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    addVertices({
        // positions      rgba                    texture coords
        {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}, // top right
        {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // bottom right
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, // bottom left
        {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f} // top left
    });

    addIndices(std::vector<unsigned int> {0, 1, 3, 1, 2, 3});

    glGenBuffers(OBJ_SIZE, gl_buffer_obj);

    vectorToArray();

    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_obj[VBO]); // pos + rgba
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<T>) * (pVertices[size_pVertices - 1].vecVertex.size()),
                    pVertexArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_buffer_obj[EBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * totalIndices, (const void*)(pIndices), GL_STATIC_DRAW);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);; // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on currently bound textures)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y 
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT); // z 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // not using GL_TEXTURE_MIPMAP_MIN because mipmap level is 0 below.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (imgLoader.getData()) {
        // first param: specify the texture target.
        // second param: mipmap level for which we want to create a texture for. 
        // third param: what kind of format to store the texture.
        // fourth, fifth param: sets the width, height of the resulting texture.
        // sixth param: should always be zero (legacy)
        // seventh, eighth param: specify the foramt and datatype of the source image. 
        // ninth param: 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
            imgLoader.getWidth(), imgLoader.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgLoader.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    imgLoader.releaseImgMem();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, rgba));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (const void*)offsetof(Vertex<T>, texture));
    glEnableVertexAttribArray(2);
}



#endif