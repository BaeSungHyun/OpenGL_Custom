#include <glLight.h>

GlLight::GlLight() :
    ambient(glm::vec3(1.0f)),
    diffuse(glm::vec3(1.0f)),
    specular(glm::vec3(1.0f))    
{
}

void GlLight::setAmbient(const glm::vec3 input) {
        ambient = input;
}

void GlLight::setDiffuse(const glm::vec3 input) {
    diffuse = input;
}

void GlLight::setSpecular(const glm::vec3 input) {
    specular = input;
}

glm::vec3 GlLight::getAmbient() const {
    return ambient;
}

glm::vec3 GlLight::getDiffuse() const {
    return diffuse;
}

glm::vec3 GlLight::getSpecular() const {
    return specular;
}

glm::vec3 GlLight::getCombined() const {
    return ambient * diffuse * specular;
}