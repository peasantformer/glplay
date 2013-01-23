#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include <src/renderer/camera.h>
#include <src/world/objects/worldobject.h>

class PlayerCamera : public WorldObject
{
public:
    PlayerCamera(std::string const& name);
    virtual ~PlayerCamera();

    glm::vec3 getFacingDirection();
    glm::vec3 getUpDirection();
    glm::vec3 getSideDirection();

protected:
    virtual void populateData(GLMeshSource & source);
};

#endif // PLAYERCAMERA_H
