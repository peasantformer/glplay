#include "glframe.h"

GLFrame::GLFrame()
{
}

void GLFrame::addPacket(GLPacket *packet)
{
    packets.push_back(std::shared_ptr<GLPacket>(packet));
}

void GLFrame::addPacket(std::shared_ptr<GLPacket> packet)
{
    packets.push_back(packet);
}
