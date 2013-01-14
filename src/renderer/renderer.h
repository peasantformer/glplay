#ifndef RENDERER_H
#define RENDERER_H

#include <src/base/gamethread.h>

class GLFWwindow;

class Renderer : public GameThread
{
public:
    Renderer(int width, int height);
    virtual ~Renderer();

    void operator()();

private:
    void init();

    int width;
    int height;

    GLFWwindow * window;
};

#endif // RENDERER_H
