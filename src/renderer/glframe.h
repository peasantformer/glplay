#ifndef GLFRAME_H
#define GLFRAME_H

#include <src/renderer/packets/glpacket.h>

#include <src/renderer/camera.h>

#include <vector>
#include <memory>

class GLRender;
class GLCompile;

class GLFrame
{
public:
    GLFrame();

    Camera camera;

    void addPacket(std::shared_ptr<GLRender> packet);
    void addPacket(std::shared_ptr<GLCompile> packet);

    std::vector<std::shared_ptr<GLRender> > renderPackets;
    std::vector<std::shared_ptr<GLCompile> > compilePackets;
};

#endif // GLFRAME_H
