#ifndef GLLIGHT_H
#define GLLIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Starting from here, it's 'old' branch

class GlLight {
public:
    GlLight();

    void setAmbient(const glm::vec3&);
    void setDiffuse(const glm::vec3&);
    void setSpecular(const glm::vec3&);
    void setLightPos(const glm::vec3&);

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;

    glm::vec3 getCombined() const;
    glm::vec3 getLightPos() const;
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 lightPos;
};

#endif