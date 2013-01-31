#include "glcompile.h"

#include <src/renderer/renderer.h>

GLCompile::GLCompile()
    : compiled(false)
{
}

GLCompile::~GLCompile()
{
}

void GLCompile::visit(Renderer &renderer)
{
    // do nothing
}

void GLCompile::wait()
{
    if (compiled) return;

    std::unique_lock<std::mutex> lock(mutex);

    while (!compiled) {
        cond.wait(lock);
    }
}

void GLCompile::notify()
{
    compiled = true;
    cond.notify_one();
}

