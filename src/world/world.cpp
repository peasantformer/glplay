#include "world.h"

#include <src/world/actions/worldaction.h>


World::World()
    : GameThread(30)
    , frames(2)
{
}

World::~World()
{
}

void World::operator ()()
{
    init();
    while (!isDone()) {
        beginTick();
        processNewObjects();
        processActions();
        evaluateWorld();
        selectObjectsToRender();
        endTick();
    }
    deinit();

}

void World::addAction(std::shared_ptr<WorldAction> action)
{
    actions.try_push(action);
}

void World::addPlayer(std::shared_ptr<Player> player)
{
    players.newObjects.try_push(player);
}

void World::addProp(std::shared_ptr<Prop> prop)
{
    props.newObjects.try_push(prop);
}

bool World::getFrame(GLFrame &frame)
{
    return frames.try_pop(frame);
}
