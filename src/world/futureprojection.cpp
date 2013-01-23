#include "futureprojection.h"

FutureProjection::FutureProjection()
{
}

Projection FutureProjection::getAndFlush()
{
    Projection p = projection;

    projection = Projection();
    return p;
}

void FutureProjection::setSpeed(float value)
{
    projection.speed = value;
}

void FutureProjection::setDirection(glm::vec3 direction)
{
    projection.translation = direction;
    if (glm::length(projection.translation) > 0.0f) {
        projection.translation = glm::normalize(projection.translation);
    }
}

void FutureProjection::addDirection(glm::vec3 direction)
{
    projection.translation += direction;
    if (glm::length(projection.translation) > 0.0f) {
        projection.translation = glm::normalize(projection.translation);
    }
}

void FutureProjection::setPosition(glm::vec3 position)
{
    projection.translation = position;
}

void FutureProjection::setPitch(float angle)
{
    projection.rotations.pitch = angle;
}

void FutureProjection::setRoll(float angle)
{
    projection.rotations.roll = angle;
}

void FutureProjection::setYaw(float angle)
{
    projection.rotations.yaw = angle;
}

void FutureProjection::addPitch(float angle)
{
    projection.rotations.pitch += angle;
}

void FutureProjection::addRoll(float angle)
{
    projection.rotations.roll += angle;
}

void FutureProjection::addYaw(float angle)
{
    projection.rotations.yaw += angle;
}

