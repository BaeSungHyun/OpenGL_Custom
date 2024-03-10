#version 400 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform vec4 uniColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;

// uniform vec4 ourColor; // uniform variable is unique per shader program object. 
// can be accessed from any shader at any stage in the shader program.

void main() {
    // FragColor = uniColor;
    // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor);
    FragColor = texture(ourTexture, TexCoord) * vec4(lightColor, 1.0);
}