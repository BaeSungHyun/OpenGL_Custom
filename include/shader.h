#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream> // file stream
#include <sstream> // string stream
#include <iostream> // input output stream
#include <initializer_list>



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
    int findUniformLocation(const std::string& name) const; 

    void changeUniformFloat(const int& loc, const std::initializer_list<float>& value) const; 
    void changeUniformGlm(const int& loc, const float* value) const;
    void setTextureUnit(const int& loc, const int& num) const;
};


#endif