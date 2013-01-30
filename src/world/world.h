#ifndef WORLD_H
#define WORLD_H

#include <src/base/gamethread.h>

#include <src/renderer/glframe.h>

#include <src/util/blockingqueue.h>

#include <src/world/worldcontainer.h>

class WorldAction;
class KeyPress;
class MouseMove;

class Player;
class Prop;

class World : public GameThread
{
public:
    World();
    virtual ~World();
    void operator ()();

    void addAction(std::shared_ptr<WorldAction> action);
    void addPlayer(std::shared_ptr<Player>      player);
    void addProp(std::shared_ptr<Prop>          prop);

    virtual void action(KeyPress  & action) = 0;
    virtual void action(MouseMove & action) = 0;

    bool getFrame(GLFrame &frame);

protected:
    BlockingQueue<GLFrame> frames;
    BlockingQueue<std::shared_ptr<WorldAction> > actions;

    WorldContainer<Player> players;
    WorldContainer<Prop> props;

    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void processNewObjects() = 0;
    virtual void processActions() = 0;
    virtual void evaluateWorld() = 0;
    virtual void selectObjectsToRender() = 0;
};

#endif // WORLD_H
