#ifndef GLFRAME_H
#define GLFRAME_H

#include <src/renderer/packets/glpacket.h>

#include <src/renderer/camera.h>

#include <vector>
#include <memory>

class GLFrame
{
public:
    GLFrame();

    Camera camera;

    void addPacket(GLPacket * packet);
    void addPacket(std::shared_ptr<GLPacket> packet);

    std::vector<std::shared_ptr<GLPacket> > packets;
};

#endif // GLFRAME_H
