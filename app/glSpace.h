#ifndef GLSPACE_H
#define GLSPACE_H

#define GLM_ENABLE_EXPERIMENTAL
// 1. Local Space (Object Space) -- Model Matrix (Object Matrix) --> 
// 2. World Space -- View Matrix (Inverse of Eye Matrix) --> 
// 3. View Space (Eye Space) -- Projection Matrix --> 
// 4. Clip Space (NDC, perspective division on end of vertex shader) -- ViewPort Transform -->
// 5. Screen Space
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class GlSpace {
public:
    GlSpace();
    ~GlSpace();
    
    void rotateObjectR(const float& angleDegrees, const glm::vec3& axis);
    void translateObjectT(const glm::vec3& translation);

    void rotateViewR(const float& angleDegrees, const glm::vec3& axis);
    void translateViewT(const glm::vec3& translation);

    void perspective(const float&, const float&, const float&, const float&, const float&);
    void ortho();

    glm::mat4 getObjectMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspective() const;
    glm::mat4 getOrtho() const;
    
private:
    glm::mat4 mObjectT; // Object (Model) Matrix ( Translate Part )
    glm::mat4 mObjectR; // Object (Model) Matrix ( Rotate part )
    glm::quat qObjectR; // Object (Model) Quaterrnion ( Rotate Part )

    glm::mat4 mViewT; // View Matrix - Inverse of Eye Matrix ( Translate Part )
    glm::mat4 mViewR; // View Matrix - Inverse of Eye Matrix ( Rotate Part )
    glm::quat qViewR; // View Quaternion ( Rotate Part )

    glm::mat4 mPerspetiveProj; // Perspective Projection Matrix

    glm::mat4 mOrthoProj; // Ortho Projection Matrix
};




#endif