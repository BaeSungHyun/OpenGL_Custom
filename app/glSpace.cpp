#include "glSpace.h"

GlSpace::GlSpace() :
    mObjectT(glm::mat4(1.0f)), mObjectR(glm::mat4(1.0f)), // Object Matrix (Translation + Rotation)
    qObjectR(glm::qua(1.0f, 0.0f, 0.0f, 0.0f)), // Object Quaternion for Rotation
    mViewT(glm::mat4(1.0f)), mViewR(glm::mat4(1.0f)), // View Matrix (Translation + Rotation)
    qViewR(glm::qua(1.0f, 0.0f, 0.0f, 0.0f)), // View Quaternion for Rotation
    mEyeT(glm::mat4(1.0f)), mEyeR(glm::mat4(1.0f)), // Eye Matrix (Translation + Rotation)
    qEyeR(glm::qua(1.0f, 0.0f, 0.0f, 0.0f)), // Eye Quaternion for Rotation
    cameraPos(), cameraTarget(), cameraX(), cameraY(), cameraZ() // camera Vectors default initialized
{
    // all matrix initialized with Identity Matrix
    // Quaternion initialized to w = 1.0f and other = 0.0f
}

GlSpace::~GlSpace() {

}

// Object (Model) Matrix
void GlSpace::rotateObjectRPost(const float& angleDegrees, const glm::vec3& axis) {
    float angleRadians = glm::radians(angleDegrees);
    // Create a quaternion representing the rotation
    qObjectR = glm::angleAxis(angleRadians, glm::normalize(axis));
    mObjectR = glm::toMat4(qObjectR) * mObjectR; // alter the order for global rotation upon Three-Axis (x,y,z)
}

void GlSpace::translateObjectT(const glm::vec3& translation) {
    // mObjectT = glm::translate(mObjectT, translation);
    mObjectT[3] = mObjectT[3] + glm::vec4(translation, 0.0f);
}

// View Matrix (Inverse of Eye Matrix) --- Deprecated, use Eye instead
void GlSpace::rotateViewR(const float& angleDegrees, const glm::vec3& axis) {
    float angleRadians = glm::radians(angleDegrees);
    // Create a quaternion representing the rotation
    qViewR = glm::angleAxis(angleRadians, glm::normalize(axis));
    mViewR = mViewR * glm::toMat4(qViewR);
}
// --- Deprecated, use Eye instead
void GlSpace::translateViewT(const glm::vec3& translation) {
    // mViewT = glm::translate(mViewT, translation);
    mViewT[3] = mViewT[3] + glm::vec4(translation, 0.0f);
}

// Eye Matrix
void GlSpace::rotateEyeR(const float& angleDegrees, const glm::vec3& axis) {
    float angleRadians = glm::radians(angleDegrees);
    // Create a quaternion representing the rotation
    qEyeR = glm::angleAxis(angleRadians, glm::normalize(axis));
    mEyeR = mEyeR * glm::toMat4(qEyeR);
}

void GlSpace::translateEyeT(const glm::vec3& translation) {
    mEyeT[3] = mEyeT[3] + glm::vec4(translation, 0.0f);
}

void GlSpace::convertEyeToView() {
    mViewT[3] = glm::vec4(-mEyeT[3][0], -mEyeT[3][1], -mEyeT[3][2], 1.0f);

    mViewR[0] = mEyeR[0];
    mViewR[1] = mEyeR[1];
    mViewR[2] = mEyeR[2];
    mViewR = glm::transpose(mViewR);
}

// Projection Matrix
void GlSpace::perspective(const float& fovDegree, const float& width, 
    const float& height, const float& zNear, const float& zFar) {
    mPerspetiveProj = glm::perspective(glm::radians(fovDegree), width / height, zNear, zFar);
}

void GlSpace::ortho() {
    
}


// Camera Methods
void GlSpace::setCamPos(const glm::vec3& pos) {
    cameraPos = pos;
}

void GlSpace::setCamTar(const glm::vec3& tar) {
    cameraTarget = tar;
}

void GlSpace::setCamAxes() {
    cameraZ = glm::normalize(cameraPos - cameraTarget); // Z-Axis
    cameraX = glm::normalize(glm::cross(up, cameraZ));
    cameraY = glm::cross(cameraZ, cameraX);
}

void GlSpace::setViewTByCam() {
    mViewT[3] = glm::vec4(-cameraPos, 1.0f);
    mEyeT[3] = glm::vec4(cameraPos, 1.0f);
}

void GlSpace::setViewRByCam() {
    mViewR[0] = glm::vec4(cameraX, 0.0f);
    mViewR[1] = glm::vec4(cameraY, 0.0f);
    mViewR[2] = glm::vec4(cameraZ, 0.0f);
    mViewR = glm::transpose(mViewR);

    mEyeR[0] = glm::vec4(cameraX, 0.0f);
    mEyeR[1] = glm::vec4(cameraY, 0.0f);
    mEyeR[2] = glm::vec4(cameraZ, 0.0f);
}


// Getter
glm::mat4 GlSpace::getObjectMatrix() const {
    return mObjectR * mObjectT;
}

glm::mat4 GlSpace::getViewMatrix() const {
    return mViewR * mViewT; // Reverse Order because mEyeT * mEyeR
}

glm::mat4 GlSpace::getPerspective() const {
    return mPerspetiveProj;
}

glm::mat4 GlSpace::getOrtho() const {
    return mOrthoProj;
}


