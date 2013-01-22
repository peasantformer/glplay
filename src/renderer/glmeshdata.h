#ifndef GLMESHDATA_H
#define GLMESHDATA_H

#include <src/renderer/shaderprogram.h>

#include <glm/glm.hpp>

#include <functional>

class GLMeshData
{
public:
    GLMeshData();
    virtual ~GLMeshData();

    bool compiled;

    unsigned int vboData;
    unsigned int vboIndices;
    unsigned int vertices;
    unsigned int shaderProgram;

    glm::mat4 model;

    std::function<void(ShaderProgram &)> shaderPopulator;
};

#endif // GLMESHDATA_H
