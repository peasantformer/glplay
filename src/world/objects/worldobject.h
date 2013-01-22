#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <src/renderer/glmeshdata.h>
#include <src/renderer/glmeshsource.h>
#include <src/world/projection.h>

#include <memory>

class WorldObject
{
public:
    WorldObject(std::string const& name);
    virtual ~WorldObject();

    std::string const& name;

    Projection projection;

    GLMeshData data;

    GLMeshSource const& loadData();

protected:
    virtual void populateData(GLMeshSource & source) = 0;

private:
    bool populated;
    std::shared_ptr<GLMeshSource> source;
};

#endif // WORLDOBJECT_H
