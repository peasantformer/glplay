#ifndef ENGINE_H
#define ENGINE_H

#include <src/base/gamethread.h>

#include <thread>

class Renderer;
class World;
class WorldObject;

class Engine : public GameThread
{
public:
    Engine(Renderer & renderer, World & world);
    virtual ~Engine();

    void operator ()();

    void wait();

    void addObject(WorldObject * object);
    void addObject(std::shared_ptr<WorldObject> object);

private:
    Renderer & renderer;
    World & world;

    std::thread t_engine;
    std::thread t_renderer;
    std::thread t_world;

    void init();
    void deinit();
    void exchangeObjects();

};

#endif // ENGINE_H
