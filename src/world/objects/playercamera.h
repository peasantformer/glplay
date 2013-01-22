#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include <src/world/objects/worldobject.h>

class PlayerCamera : public WorldObject
{
public:
    PlayerCamera(std::string const& name);
    virtual ~PlayerCamera();

protected:
    virtual void populateData(GLMeshSource & source);
};

#endif // PLAYERCAMERA_H
