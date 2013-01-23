#include "world.h"

#include <src/world/actions/worldaction.h>
#include <src/world/objects/worldobject.h>

#include <iostream>

World::World()
    : GameThread(30)
    , frames(2)
    , engine(0)
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

void World::addObject(WorldObject *object)
{
    newObjects.try_push(std::shared_ptr<WorldObject>(object));
}

void World::addObject(std::shared_ptr<WorldObject> object)
{
    newObjects.try_push(object);
}

void World::addAction(WorldAction *action)
{
    actions.try_push(std::shared_ptr<WorldAction>(action));
}

void World::addAction(std::shared_ptr<WorldAction> action)
{
    actions.try_push(action);
}


bool World::getFrame(GLFrame & frame)
{
    return frames.try_pop(frame);
}

void World::setEngine(Engine *e)
{
    engine = e;
}

/*
void World::move(PlayerMovement &movement)
{
    std::map<std::string, std::shared_ptr<WorldObject> >::iterator end, cam;
    end = objects.end();
    cam = objects.find("Player");

    if (cam != end) {
        PlayerCamera * playerCamera = (PlayerCamera*) cam->second.get();
        FutureProjection & fp = cam->second->futureProjection;
        glm::vec3 dir;

        // illogical
        switch (movement.direction) {
        case PlayerMovement::Forward:
            dir = playerCamera->getFacingDirection();
            break;
        case PlayerMovement::Backward:
            dir = playerCamera->getFacingDirection() * -1.0f;
            break;
        case PlayerMovement::StrafeLeft:
            dir = playerCamera->getSideDirection();
            break;
        case PlayerMovement::StrafeRight:
            dir = playerCamera->getSideDirection() * -1.0f;
            break;
        case PlayerMovement::FlyDown:
            dir = playerCamera->getUpDirection(); // and this is !
            break;
        case PlayerMovement::FlyUp:
            dir = playerCamera->getUpDirection()  * -1.0f; // this
            break;
        }

        fp.setDirection(dir);
    }

}

void World::processNewObjects()
{
    std::shared_ptr<WorldObject> newObj;
    while (newObjects.try_pop(newObj)) {
        objects[newObj->name] = newObj;
    }
}

void World::processActions()
{
    std::shared_ptr<WorldAction> action;
    while (actions.try_pop(action)) {
        action->visit(*this);
    }
}

void World::evaluateWorld()
{
}

void World::selectObjectsToRender()
{
    if (frames.full()) return;

    GLFrame frame;

    std::map<std::string, std::shared_ptr<WorldObject> >::iterator it, end, cam;
    end = objects.end();
    cam = objects.find("Player");

    if (cam != end) {
        Projection diff = cam->second->futureProjection.getAndFlush();

        cam->second->projection.translation += diff.translation;

        frame.camera.setProjection(cam->second->projection);
    }

    for (it = objects.begin(); it != end; it++) {
        GLMeshData & mesh = it->second->data;
        if (mesh.compiled == false) continue;
        frame.addPacket(new GLRender(mesh));
    }
    frames.try_push(frame);
}

*/
