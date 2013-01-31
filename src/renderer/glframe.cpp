#include "glframe.h"

GLFrame::GLFrame()
{
}

void GLFrame::addPacket(std::shared_ptr<GLRender> packet)
{
    renderPackets.push_back(packet);
}

void GLFrame::addPacket(std::shared_ptr<GLCompile> packet)
{
    compilePackets.push_back(packet);
}

