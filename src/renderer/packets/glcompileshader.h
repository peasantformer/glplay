#ifndef GLCOMPILESHADER_H
#define GLCOMPILESHADER_H

#include <src/renderer/packets/glcompile.h>

#include <functional>
#include <string>
#include <vector>

class GLMeshSource;

class GLCompileShader : public GLCompile
{
public:
    enum ShaderType {
        Vertex,
        Fragment
    };

    class ShaderSource {
    public:
        ShaderSource(ShaderType type, std::string const& source);
        std::string const& getSource();
        ShaderType getType();

    private:
        ShaderType type;
        std::string source;
    };

    std::vector<ShaderSource> const& shaderSources;
    std::function<void(unsigned int, std::string const&)> callback;

    GLCompileShader();
    GLCompileShader(GLMeshSource const& source);
    virtual ~GLCompileShader();
    virtual void visit(Renderer &renderer);

    void compiled(unsigned int p, std::string const& ms);
};

#endif // GLCOMPILESHADER_H
