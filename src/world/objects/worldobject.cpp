#include "worldobject.h"

WorldObject::WorldObject(const std::string &name)
    : populated(false)
    , name(name)
{
}

WorldObject::~WorldObject()
{
}

const GLMeshSource &WorldObject::loadData()
{
    if (!populated) {
        source = std::shared_ptr<GLMeshSource>(new GLMeshSource);
        populateData(*source);
    }
    return *source;
}
