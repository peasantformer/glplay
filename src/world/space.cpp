#include "space.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream> // temp

Space::Space(float yaw, float roll, float pitch)
{
    setOrientation(yaw,roll,pitch);
}

Space::Space(const glm::vec3 &position)
{
    translate(position);
}

Space::Space(const glm::vec3 &position, float yaw, float roll, float pitch)
{
    setOrientation(yaw,roll,pitch);
    translate(position);
}

Space::Space()
{
}

Space & Space::operator *(const Space &rhs)
{
    if (&rhs == this) return *this;
    rotationQuat = rotationQuat * rhs.rotationQuat;
    transformMat = transformMat * rhs.transformMat;
    return *this;
}

void Space::translate(const glm::vec3 &translation)
{
    transformMat = glm::translate(transformMat,translation);
}

void Space::setOrientation(float yaw, float roll, float pitch)
{
    //rotationQuat = glm::quat(glm::vec3(pitch,yaw,roll));
    rotationQuat = glm::quat();
    rotationQuat = glm::rotate(rotationQuat, yaw+180, glm::vec3(0.0f, 0.0f, 1.0f));
    rotationQuat = glm::rotate(rotationQuat, roll+180, glm::vec3(0.0f, 1.0f, 0.0f));
    rotationQuat = glm::rotate(rotationQuat, pitch-90, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Space::rotate(float angle, const glm::vec3 &axis)
{
    rotationQuat = glm::rotate(rotationQuat,angle,axis);
}

void Space::scale(const glm::vec3 &axis)
{
    transformMat = glm::scale(transformMat,axis);
}

glm::vec3 Space::getForwardDirection()
{
    return glm::vec3(0.0f, 0.0f, 1.0f) * glm::mat3_cast(rotationQuat);
}

glm::vec3 Space::getSideDirection()
{
    return glm::vec3(-1.0f, 0.0f, 0.0f) * glm::mat3_cast(rotationQuat);
}

glm::vec3 Space::getUpDirection()
{
    return glm::vec3(0.0f, -1.0f, 0.0f) * glm::mat3_cast(rotationQuat);
}

glm::vec3 Space::getTranslation()
{
    return glm::vec3(transformMat[3]);
}

glm::mat4 Space::getMatrix() const
{
    return glm::mat4_cast(rotationQuat) * transformMat;
}

