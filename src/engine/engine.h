#ifndef ENGINE_H
#define ENGINE_H

#include <src/base/gamethread.h>

#include <thread>

class Renderer;

class Engine : public GameThread
{
public:
    Engine(Renderer & renderer);
    virtual ~Engine();

    void operator()();

    void waitTillFinish();

private:
    void init();
    Renderer & renderer;

    std::thread t_engine;
    std::thread t_renderer;
};

#endif // ENGINE_H
