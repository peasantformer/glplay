#ifndef GLOPUPLOAD_H
#define GLOPUPLOAD_H

#include <src/renderer/gloperation.h>

#include <mutex>
#include <condition_variable>

class GLOPUpload : public GLOperation
{
public:
    GLOPUpload();
    void visit(Renderer &renderer);
    void waitForUpload();

protected:
    void doneNotify();

private:
    bool uploaded;
    std::mutex mutex;
    std::condition_variable cond;
};

#endif // GLOPUPLOAD_H
