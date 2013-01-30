#include "camera.h"

#include <iostream> // temprory

#include <glm/gtx/euler_angles.hpp>

Camera::Camera()
    : fov(60.0f)
    , near(0.1f)
    , far(100.0f)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getMVP(float width, float height) const
{
    glm::mat4 proj;

    proj *= glm::perspectiveFov<float>(fov, width, height, near, far);

    // i am using Z-up coordinate system.
    //glm::mat4 rotmat;


    //rotmat = glm::rotate(rotmat,pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    //rotmat = glm::rotate(rotmat,yaw,glm::vec3(0.0f, 0.0f, 1.0f));
    //rotmat = glm::rotate(rotmat,roll,glm::vec3(0.0f, 1.0f, 0.0f));

    // after yawPitchRoll:
    //rotmat = glm::yawPitchRoll(glm::radians(roll),glm::radians(pitch),glm::radians(yaw));
    // workse except that roll is along Z axis


    //view = glm::inverse(glm::translate(view,translation));


    //return proj * rotmat * view;

    return proj * space.getMatrix();
}

/*
void Camera::setProjection(Projection &projection)
{
    translation = projection.translation;
    shiftPitch(projection.rotations.pitch);
    shiftRoll(projection.rotations.roll);
    shiftYaw(projection.rotations.yaw);
    std::cout << projection.rotations.pitch << " " << projection.rotations.roll << " " << projection.rotations.yaw << "\n";
}
*/

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
