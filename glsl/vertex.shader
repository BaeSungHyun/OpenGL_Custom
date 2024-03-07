#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 object;
uniform mat4 view;
uniform mat4 center;
uniform mat4 eyeR;
uniform mat4 projection;

void main() {
    // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = projection * eyeR * center * view * object * vec4(aPos, 1.0);
    // gl_Position = projection * center * view * object * vec4(aPos, 1.0);
    ourColor = aColor;
}