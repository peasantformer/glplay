#include "camera.h"

#include <iostream> // temprory

#include <glm/gtx/euler_angles.hpp>

Camera::Camera()
    : roll(0.0f)
    , pitch(0.0f)
    , yaw(0.0f)
    , fov(60.0f)
    , near(0.1f)
    , far(100.0f)
    , translation(0.0f, 0.0f, 0.0f)
{
}

glm::mat4 Camera::getMVP(float width, float height) const
{
    glm::mat4 proj;
    glm::mat4 view;

    proj *= glm::perspectiveFov<float>(fov, width, height, near, far);

    // i am using Z-up coordinate system.
    glm::mat4 rotmat;


    rotmat = glm::rotate(rotmat,pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    rotmat = glm::rotate(rotmat,yaw,glm::vec3(0.0f, 0.0f, 1.0f));
    rotmat = glm::rotate(rotmat,roll,glm::vec3(rotmat[0][2], rotmat[1][2], rotmat[2][2]));

    // after yawPitchRoll:
    //rotmat = glm::yawPitchRoll(glm::radians(roll),glm::radians(pitch),glm::radians(yaw));
    // workse except that roll is along Z axis


    view = glm::inverse(glm::translate(view,translation));


    return proj * rotmat * view;
}


glm::vec3 Camera::getFacingDirection()
{
    glm::mat4 rotmat;
    rotmat = glm::rotate(rotmat,pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    rotmat = glm::rotate(rotmat,roll,glm::vec3(0.0f, 1.0f, 0.0f));
    rotmat = glm::rotate(rotmat,yaw,glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::vec3(rotmat[0][2], rotmat[1][2], rotmat[2][2]) * -1.0f;
}

glm::vec3 Camera::getUpDirection()
{
    glm::mat4 rotmat;

    rotmat = glm::rotate(rotmat,pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    rotmat = glm::rotate(rotmat,yaw,glm::vec3(0.0f, 0.0f, 1.0f));
    rotmat = glm::rotate(glm::mat4(),roll,glm::vec3(rotmat[0][2], rotmat[1][2], rotmat[2][2]));

    return glm::vec3(rotmat * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
}

void Camera::setProjection(Projection &projection)
{
    translation = projection.position;
    setPitch(projection.rotations.pitch);
    setRoll(projection.rotations.roll);
    setYaw(projection.rotations.yaw);
}

void Camera::shiftNear(float value)
{
    near += value;
}

void Camera::shiftFar(float value)
{
    far += value;
}

void Camera::shiftFov(float value)
{
    fov += value;
}

void Camera::shiftRoll(float value)
{
    //direction = glm::rotate(glm::mat4(), -value, glm::vec3(0.0f, 1.0f, 0.0f)) * direction;
    //direction = glm::normalize(direction);

    roll += value;
    if (roll > 360) roll = 0;
    if (roll <   0) roll = 360;
}

void Camera::shiftPitch(float value)
{
    //direction = glm::rotate(glm::mat4(), -value, glm::vec3(1.0f, 0.0f, 0.0f)) * direction;
    //direction = glm::normalize(direction);

    pitch += value;
    if (pitch > 360) pitch = 0;
    if (pitch <   0) pitch = 360;
}

void Camera::shiftYaw(float value)
{
    //direction = glm::rotate(glm::mat4(), -value, glm::vec3(0.0f, 0.0f, 1.0f)) * direction;
    //direction = glm::normalize(direction);

    yaw += value;
    if (yaw > 360) yaw = 0;
    if (yaw <   0) yaw = 360;
}

void Camera::setNear(float value)
{
    near = value;
}

void Camera::setFar(float value)
{
    far = value;
}

void Camera::seFov(float value)
{
    fov = value;
}

void Camera::setRoll(float value)
{
    roll = value;
}

void Camera::setPitch(float value)
{
    pitch = value;
}

void Camera::setYaw(float value)
{
    yaw = value;
}

float Camera::getNear()
{
    return near;
}

float Camera::getFar()
{
    return far;
}

float Camera::getFov()
{
    return fov;
}

float Camera::getRoll()
{
    return roll;
}

float Camera::getPitch()
{
    return pitch;
}

float Camera::getYaw()
{
    return yaw;
}

glm::vec3 Camera::extractVec3FromVec4(const glm::vec4 &source) const
{
    return glm::vec3(source.x, source.y, source.z);
}
