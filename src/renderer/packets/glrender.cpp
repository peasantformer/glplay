#include "glrender.h"

#include <src/renderer/renderer.h>

GLRender::GLRender()
    : data(GLMeshData())
{
}

GLRender::GLRender(const GLMeshData &data)
    : data(data)
{
}

GLRender::~GLRender()
{
}

void GLRender::visit(Renderer &renderer)
{
    renderer.render(*this);
}
