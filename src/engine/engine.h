#ifndef ENGINE_H
#define ENGINE_H

#include <src/base/gamethread.h>

#include <thread>

class Renderer;
class World;
class WorldObject;
class GLFWwindow;

class Engine : public GameThread
{
public:
    Engine(Renderer & renderer, World & world);
    Engine(std::shared_ptr<Renderer> renderer, std::shared_ptr<World> world);
    virtual ~Engine();

    void operator ()();

    void wait();

    void addObject(WorldObject * object);
    void addObject(std::shared_ptr<WorldObject> object);

    static void keyFunStatic(GLFWwindow * win, int key, int state);
    static void cursorFunStatic(GLFWwindow * win, int x, int y);
    void keyFun(int key, int state);
    void cursorFun(int x, int y);

private:
    Renderer & renderer;
    World & world;

    std::thread t_engine;
    std::thread t_renderer;
    std::thread t_world;

    void init();
    void deinit();
    void processInput();
    void exchangeObjects();

};

#endif // ENGINE_H
