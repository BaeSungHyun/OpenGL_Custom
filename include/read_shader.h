#ifndef READ_SHADER_H
#define READ_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const char* readShader(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    char* dynamicBuffer = nullptr;
    if (fileStream.is_open()) {
        std::string content((std::istreambuf_iterator<char>(fileStream)),
                            std::istreambuf_iterator<char>());
        dynamicBuffer = new char[content.size() + 1];
        std::copy(content.begin(), content.end(), dynamicBuffer);
        dynamicBuffer[content.size()] = '\0'; // Null-terminating the string

        fileStream.close();
    }

    return dynamicBuffer;
}

#endif