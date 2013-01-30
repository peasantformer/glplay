#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <src/renderer/glmeshdata.h>
#include <src/renderer/glmeshsource.h>

#include <memory>

class Renderable
{
public:
    GLMeshData data;

    virtual ~Renderable();
    GLMeshSource const& loadData();
protected:
    virtual void populateData(GLMeshSource & source) = 0;

private:
    bool populated;
    std::shared_ptr<GLMeshSource> source;

};

#endif // RENDERABLE_H
