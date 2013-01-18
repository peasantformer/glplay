#include "glopupload.h"

#include <src/renderer/renderer.h>

GLOPUpload::GLOPUpload()
    : uploaded(false)
{
}

void GLOPUpload::visit(Renderer &renderer)
{
    renderer.accept(*this);
}

void GLOPUpload::waitForUpload()
{
    if (uploaded) return;

    std::unique_lock<std::mutex> lock(mutex);

    while (!uploaded) {
        cond.wait(lock);
    }
}

void GLOPUpload::doneNotify()
{
    uploaded = true;
    cond.notify_one();
}
