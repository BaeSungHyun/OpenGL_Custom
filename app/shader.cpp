#include "shader.h"
#include <type_traits>


Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // 1. retrieve the vertex / fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure lifetime objects can throw exceptions
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATON_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATON_FAILED\n" << infoLog << std::endl;
    }

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shaders; already linked to the program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


Shader::~Shader() {
    
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::deleteProgram() {
    glDeleteProgram(ID);
}

int Shader::findUniformLocation(const std::string &name) const
{
    return glGetUniformLocation(ID, name.c_str());
}

void Shader::changeUniformFloat(const int& loc, const std::initializer_list<float>& value) const{
    float temp_val[4] {};
    auto temp = value.begin();
    for (int i = 0 ; temp != value.end(); temp++, i++)
        temp_val[i] = *temp;
    glUniform4f(loc, temp_val[0], temp_val[1], temp_val[2], temp_val[3]);
}

void Shader::changeUniformMatrix4fv(const int& loc, const float* value) const {
    glUniformMatrix4fv(loc, 1, GL_FALSE, value);
}

void Shader::setTextureUnit(const int& loc, const int& num) const {
    glUniform1i(loc, num);
}

void Shader::changeUniformVector3fv(const int& loc, const float* value) const {
    glUniform3fv(loc, 1, value);
}

