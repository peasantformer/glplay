#include "world.h"

World::World()
    : GameThread(30)
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
        endTick();
    }
    deinit();
}


void World::init()
{

    initNotify();
}

void World::deinit()
{
}
