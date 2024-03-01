#include "glSpace.h"

GlSpace::GlSpace() :
    mObjectT(glm::mat4(1.0f)), mObjectR(glm::mat4(1.0f)),
    qObjectR(glm::qua(1.0f, 0.0f, 0.0f, 0.0f)),
    mViewT(glm::mat4(1.0f)), mViewR(glm::mat4(1.0f)),
    qViewR(glm::qua(1.0f, 0.0f, 0.0f, 0.0f))
{
    // all matrix initialized with Identity Matrix
    // Quaternion initialized to w = 1.0f and other = 0.0f
}

GlSpace::~GlSpace() {

}

// Object (Model) Matrix
void GlSpace::rotateObjectR(const float& angleDegrees, const glm::vec3& axis) {
    float angleRadians = glm::radians(angleDegrees);
    // Create a quaternion representing the rotation
    qObjectR = glm::angleAxis(angleRadians, glm::normalize(axis));
    mObjectR = mObjectR * glm::toMat4(qObjectR);
}

void GlSpace::translateObjectT(const glm::vec3& translation) {
    mObjectT = glm::translate(mObjectT, translation);
}


// View Matrix (Inverse of Eye Matrix)
void GlSpace::rotateViewR(const float& angleDegrees, const glm::vec3& axis) {
    float angleRadians = glm::radians(angleDegrees);
    // Create a quaternion representing the rotation
    qViewR = glm::angleAxis(angleRadians, glm::normalize(axis));
    mViewR = mViewR * glm::toMat4(qViewR);
}

void GlSpace::translateViewT(const glm::vec3& translation) {
    mViewT = glm::translate(mViewT, translation);
}

void GlSpace::perspective(const float& fovDegree, const float& width, 
    const float& height, const float& zNear, const float& zFar) {
    mPerspetiveProj = glm::perspective(glm::radians(fovDegree), width / height, zNear, zFar);
}

void GlSpace::ortho() {

}


// Getter
glm::mat4 GlSpace::getObjectMatrix() const {
    return mObjectT * mObjectR;
}

glm::mat4 GlSpace::getViewMatrix() const {
    return mViewT * mViewR;
}

glm::mat4 GlSpace::getPerspective() const {
    return mPerspetiveProj;
}

glm::mat4 GlSpace::getOrtho() const {
    return mOrthoProj;
}
