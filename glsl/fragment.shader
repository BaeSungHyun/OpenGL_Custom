#version 400 core

out vec4 FragColor;
in vec4 ourColor;

uniform vec4 uniColor;

// uniform vec4 ourColor; // uniform variable is unique per shader program object. 
// can be accessed from any shader at any stage in the shader program.

void main() {
    FragColor = uniColor;
}