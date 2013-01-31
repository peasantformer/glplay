#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <src/renderer/glmeshdata.h>
#include <src/renderer/glmeshsource.h>

#include <memory>
#include <map>

class Renderable
{
public:
    GLMeshData data;

    Renderable(bool cachable = true);
    virtual ~Renderable();
    GLMeshSource const& loadData();
    bool getCachable();
    std::string const& getCacheKey();

protected:
    virtual void populateData(GLMeshSource & source) = 0;
    virtual std::string genCacheKey() = 0;

private:
    bool cachable;
    bool populated;
    std::shared_ptr<GLMeshSource> source;
    std::string cacheKey;
};

#endif // RENDERABLE_H
