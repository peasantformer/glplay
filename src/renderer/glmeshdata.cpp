#include "glmeshdata.h"

GLMeshData::GLMeshData()
    : compiled(false)
    , vboData(0)
    , vboIndices(0)
    , vertices(0)
    , shaderProgram(0)
{
}

GLMeshData::~GLMeshData()
{
}
