#ifndef GLMESHSOURCE_H
#define GLMESHSOURCE_H

#include <src/renderer/packets/glcompileshader.h>

#include <vector>
#include <string>

class GLMeshSource
{
public:
    GLMeshSource();

    std::vector<float> data;
    std::vector<unsigned int> vertices;

    std::vector<GLCompileShader::ShaderSource> shaders;

};

#endif // GLMESHSOURCE_H
