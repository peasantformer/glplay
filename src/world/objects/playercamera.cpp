#include "playercamera.h"

PlayerCamera::PlayerCamera(const std::string &name)
    : WorldObject(name)
{
}

PlayerCamera::~PlayerCamera()
{
}

glm::vec3 PlayerCamera::getFacingDirection()
{
    glm::mat4 rotmat;
    rotmat = glm::rotate(rotmat,projection.rotations.pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    rotmat = glm::rotate(rotmat,projection.rotations.roll,glm::vec3(0.0f, 1.0f, 0.0f));
    rotmat = glm::rotate(rotmat,projection.rotations.yaw,glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::vec3(rotmat[0][2], rotmat[1][2], rotmat[2][2]) * -1.0f; // illogical
}

glm::vec3 PlayerCamera::getUpDirection()
{
    glm::mat4 rotmat;
    rotmat = glm::rotate(rotmat,projection.rotations.pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    rotmat = glm::rotate(rotmat,projection.rotations.roll,glm::vec3(0.0f, 1.0f, 0.0f));
    rotmat = glm::rotate(rotmat,projection.rotations.yaw,glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::vec3(rotmat[0][1], rotmat[1][1], rotmat[2][1]); // illogical
}

glm::vec3 PlayerCamera::getSideDirection()
{
    glm::mat4 rotmat;
    rotmat = glm::rotate(rotmat,projection.rotations.pitch,glm::vec3(1.0f, 0.0f, 0.0f));
    rotmat = glm::rotate(rotmat,projection.rotations.roll,glm::vec3(0.0f, 1.0f, 0.0f));
    rotmat = glm::rotate(rotmat,projection.rotations.yaw,glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::vec3(rotmat[0][0], rotmat[1][0], rotmat[2][0]) * -1.0f; // illogical
}

void PlayerCamera::populateData(GLMeshSource &source)
{
}
