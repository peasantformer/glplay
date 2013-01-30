#include "renderable.h"

Renderable::~Renderable()
{
}

const GLMeshSource &Renderable::loadData()
{
    if (!populated) {
        source = std::shared_ptr<GLMeshSource>(new GLMeshSource);
        populateData(*source);
    }
    return *source;
}
