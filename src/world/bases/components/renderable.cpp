#include "renderable.h"

Renderable::Renderable(bool cachable)
    : populated(false)
    , cachable(cachable)
{
}


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

bool Renderable::getCachable()
{
    return cachable;
}

const std::string &Renderable::getCacheKey()
{
    if (cachable && cacheKey.empty()) {
        cacheKey = genCacheKey();
    }
    return cacheKey;
}
