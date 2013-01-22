#include "glcompilegeometry.h"

#include <src/renderer/glmeshsource.h>

#include <src/renderer/renderer.h>

GLCompileGeometry::GLCompileGeometry()
    : data(std::vector<float>())
    , vertices(std::vector<unsigned int>())
{
}

GLCompileGeometry::GLCompileGeometry(const GLMeshSource &source)
    : data(source.data)
    , vertices(source.vertices)
{
}

GLCompileGeometry::~GLCompileGeometry()
{
}

void GLCompileGeometry::visit(Renderer &renderer)
{
    renderer.compile(*this);
}

void GLCompileGeometry::compiled(unsigned int d, unsigned int v, unsigned int vs)
{
    if (callback) {
        callback(d,v,vs);
    }
    notify();
}
