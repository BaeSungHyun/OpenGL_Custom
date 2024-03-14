#version 400 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 uniColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;
uniform vec3 lightPos; // Not needed if light calculation is done on view space (eye space)

// uniform vec4 ourColor; // uniform variable is unique per shader program object. 
// can be accessed from any shader at any stage in the shader program.

void main() {
    // FragColor = uniColor;
    // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor);
    // FragColor = texture(ourTexture, TexCoord) * vec4(lightColor, 1.0);
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // never become zero
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient +  diffuse);
    FragColor = vec4(result, 1.0);
}