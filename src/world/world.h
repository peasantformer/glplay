#ifndef WORLD_H
#define WORLD_H

#include <src/renderer/glframe.h>

#include <src/util/blockingqueue.h>

#include <src/base/gamethread.h>

#include <map>

class WorldObject;
class WorldAction;

class PlayerMovement;

class World : public GameThread
{
public:
    World();
    virtual ~World();
    void operator ()();

    void addObject(WorldObject * object);
    void addObject(std::shared_ptr<WorldObject> object);
    void addAction(WorldAction * action);

    bool getFrame(GLFrame & frame);

    void move(PlayerMovement & movement);

private:
    BlockingQueue<GLFrame> frames;

    BlockingQueue<std::shared_ptr<WorldAction> > actions;

    BlockingQueue<std::shared_ptr<WorldObject> > newObjects;

    std::map<std::string, std::shared_ptr<WorldObject> > objects;

    void init();
    void deinit();

    void processNewObjects();
    void processActions();
    void evaluateWorld();
    void selectObjectsToRender();
};

#endif // WORLD_H
