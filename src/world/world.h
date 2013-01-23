#ifndef WORLD_H
#define WORLD_H

#include <src/renderer/glframe.h>

#include <src/util/blockingqueue.h>

#include <src/base/gamethread.h>

#include <map>

class Engine;

class WorldObject;
class WorldAction;

class KeyPress;
class MouseMove;

class World : public GameThread
{
public:
    World();
    virtual ~World();
    void operator ()();

    void addObject(WorldObject * object);
    void addObject(std::shared_ptr<WorldObject> object);
    void addAction(WorldAction * action);
    void addAction(std::shared_ptr<WorldAction> action);

    bool getFrame(GLFrame & frame);

    virtual void action(KeyPress  & action) = 0;
    virtual void action(MouseMove & action) = 0;

    void setEngine(Engine * e);

protected:
    Engine * engine;
    BlockingQueue<GLFrame> frames;
    BlockingQueue<std::shared_ptr<WorldAction> > actions;
    BlockingQueue<std::shared_ptr<WorldObject> > newObjects;
    std::map<std::string, std::shared_ptr<WorldObject> > objects;

    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void processNewObjects() = 0;
    virtual void processActions() = 0;
    virtual void evaluateWorld() = 0;
    virtual void selectObjectsToRender() = 0;
};

#endif // WORLD_H
