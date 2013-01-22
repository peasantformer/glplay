#ifndef GLPACKET_H
#define GLPACKET_H

class Renderer;

class GLPacket
{
public:
    GLPacket();
    virtual ~GLPacket();
    virtual void visit(Renderer & renderer) = 0;
};

#endif // GLPACKET_H
