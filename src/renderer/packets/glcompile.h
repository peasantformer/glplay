#ifndef GLCOMPILE_H
#define GLCOMPILE_H

#include <src/renderer/packets/glpacket.h>

#include <mutex>
#include <condition_variable>

class GLCompile : public GLPacket
{
public:
    GLCompile();
    virtual ~GLCompile();
    virtual void visit(Renderer &renderer);
    void wait();

protected:
    void notify();

private:
    bool compiled;
    std::mutex mutex;
    std::condition_variable cond;
};

#endif // GLCOMPILE_H
