#include "glcompileshader.h"

#include <src/renderer/glmeshsource.h>

#include <src/renderer/renderer.h>

GLCompileShader::GLCompileShader()
    : shaderSources(std::vector<ShaderSource>())
{
}

GLCompileShader::GLCompileShader(const GLMeshSource &source)
    : shaderSources(source.shaders)
{
}

GLCompileShader::~GLCompileShader()
{
}

void GLCompileShader::visit(Renderer &renderer)
{
    renderer.compile(*this);
}

void GLCompileShader::compiled(unsigned int p, const std::string &ms)
{
    if (callback) {
        callback(p,ms);
    }
    notify();
}




GLCompileShader::ShaderSource::ShaderSource(GLCompileShader::ShaderType type, const std::string &source)
    : type(type)
    , source(source)
{
}

const std::string &GLCompileShader::ShaderSource::getSource()
{
    return source;
}

GLCompileShader::ShaderType GLCompileShader::ShaderSource::getType()
{
    return type;
}
