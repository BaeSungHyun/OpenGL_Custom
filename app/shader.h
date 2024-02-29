#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream> // file stream
#include <sstream> // string stream
#include <iostream> // input output stream


class Shader {
public:
    // Program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    // use/activate the shader
    void use();

    void deleteProgram();

    // utiiloty functions for setting uniform variable in GLSL
    template <typename T>
    void set(const std::string& name, T value) const;
};


#endif