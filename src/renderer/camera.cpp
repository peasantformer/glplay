#include "camera.h"

#include <iostream> // temprory

const glm::vec4 Camera::baseDirection(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 Camera::upBaseDirection(0.0f, 0.0f, 1.0f, 0.0f);

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
    /* working
    glm::mat4 proj;
    glm::mat4 view;

    proj *= glm::perspectiveFov<float>(fov, width, height, near, far);

    glm::mat4 rotmat;

    rotmat *= glm::rotate(rotmat, yaw, glm::vec3(0.0f, 0.0f, 1.0f));
    rotmat *= glm::rotate(rotmat, pitch, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec4 direction = baseDirection * rotmat;

    rotmat = glm::rotate(glm::mat4(), roll, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec4 upDirection = upBaseDirection * rotmat;

    glm::vec3 eye = translation;
    glm::vec3 center = eye + glm::vec3(direction.x, direction.y, direction.z);
    glm::vec3 up = glm::vec3(upDirection.x, upDirection.y, upDirection.z);

    view *= glm::lookAt(eye, center, up);

    return proj * view;
    */

    glm::mat4 proj;
    glm::mat4 view;

    proj *= glm::perspectiveFov<float>(fov, width, height, near, far);

    glm::mat4 rotmat;

    rotmat *= glm::rotate(rotmat, yaw, glm::vec3(0.0f, 0.0f, 1.0f));
    rotmat *= glm::rotate(rotmat, pitch, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec4 direction = glm::vec4(1.0f) * rotmat;

    //rotmat = glm::rotate(glm::mat4(), roll, glm::vec3(0.0f, 1.0f, 0.0f));

    //glm::vec4 upDirection = upBaseDirection * rotmat;

    glm::vec3 eye = translation;
    glm::vec3 center = eye + glm::vec3(direction.x, direction.y, direction.z);
    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f); //glm::vec3(upDirection.x, upDirection.y, upDirection.z);

    view *= glm::lookAt(eye, center, up);

    return proj * view;
}

glm::vec3 Camera::getFacingDirection()
{
    glm::mat4 rotmat;

    rotmat *= glm::rotate(rotmat, yaw, glm::vec3(0.0f, 0.0f, 1.0f));
    //rotmat *= glm::rotate(rotmat, roll, glm::vec3(0.0f, 1.0f, 0.0f));
    rotmat *= glm::rotate(rotmat, pitch, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec4 result = glm::vec4(1.0f) * rotmat;

    return glm::vec3(result.x, result.y, result.z);
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
    roll += value;
    if (roll > 360) roll = 0;
    if (roll <   0) roll = 360;
}

void Camera::shiftPitch(float value)
{
    pitch += value;
    if (pitch > 360) pitch = 0;
    if (pitch <   0) pitch = 360;
}

void Camera::shiftYaw(float value)
{
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
