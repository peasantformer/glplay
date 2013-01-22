#ifndef GLCOMPILEGEOMETRY_H
#define GLCOMPILEGEOMETRY_H

#include <src/renderer/packets/glcompile.h>

#include <vector>
#include <functional>

class GLMeshSource;

class GLCompileGeometry : public GLCompile
{
public:
    std::vector<float> const& data;
    std::vector<unsigned int> const& vertices;
    std::function<void(unsigned int, unsigned int, unsigned int)> callback;

    GLCompileGeometry();
    GLCompileGeometry(GLMeshSource const& source);
    virtual ~GLCompileGeometry();
    virtual void visit(Renderer &renderer);

    void compiled(unsigned int d, unsigned int v, unsigned int vs);
};

#endif // GLCOMPILEGEOMETRY_H
