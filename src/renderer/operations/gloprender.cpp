#include "gloprender.h"

#include <src/renderer/renderer.h>

GLOPRender::GLOPRender()
    : vboData(0)
    , vboIndices(0)
    , vertices(0)
    , scale(1.0f, 1.0f, 1.0f)
    , rotateAxis(0.0f, 0.0f, 0.0f)
    , rotateAngle(0)
{
}

void GLOPRender::visit(Renderer &renderer)
{
    renderer.accept(*this);
}
