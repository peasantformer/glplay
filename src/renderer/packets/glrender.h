#ifndef GLRENDER_H
#define GLRENDER_H

#include <src/renderer/packets/glpacket.h>
#include <src/renderer/glmeshdata.h>

class GLRender : public GLPacket
{
public:
    GLMeshData const& data;

    GLRender();
    GLRender(GLMeshData const& data);
    virtual ~GLRender();
    virtual void visit(Renderer &renderer);
};

#endif // GLRENDER_H
