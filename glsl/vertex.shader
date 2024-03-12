#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 Normal;

// uniform Material material;
uniform mat4 object;
uniform mat4 view;
uniform mat4 center;
uniform mat4 eyeR;
uniform mat4 projection;

void main() {
    // Need modification : try to group 'view', 'center', 'eyeR' as one
    // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = projection * eyeR * center * view * object * vec4(aPos, 1.0);
    // gl_Position = projection * center * view * object * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
    Normal = aNormal;
}