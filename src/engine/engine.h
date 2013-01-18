#ifndef ENGINE_H
#define ENGINE_H

#include <src/base/gamethread.h>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

#include <thread>

class Renderer;
class World;

class Engine : public GameThread
{
public:
    Engine(Renderer & renderer, World & world);
    virtual ~Engine();

    void operator()();

    void waitTillFinish();
    void resetPointer();
    void setListenPointer(bool value);

    static void cursorEnter(GLFWwindow * window, int entered);

private:
    void init();
    void deinit();
    Renderer & renderer;
    World & world;

    std::thread t_engine;
    std::thread t_world;
    std::thread t_renderer;

    int pointerX;
    int pointerY;
    bool listenPointer;
};

#endif // ENGINE_H
