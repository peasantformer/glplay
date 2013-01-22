#include "world.h"

#include <src/world/objects/worldobject.h>

#include <src/renderer/packets/glrender.h>

#include <iostream>

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

void World::addObject(WorldObject *object)
{
    newObjects.try_push(std::shared_ptr<WorldObject>(object));
}

void World::addObject(std::shared_ptr<WorldObject> object)
{
    newObjects.try_push(object);
}


bool World::getFrame(GLFrame & frame)
{
    return frames.try_pop(frame);
}

void World::move(PlayerMovement &movement)
{
}


void World::init()
{
    initNotify();
}

void World::deinit()
{
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
        frame.camera.setProjection(cam->second->projection);
    }

    //frame.camera.translation = glm::vec3(0.0f, 10.0f, 0.0f);
    //frame.camera.setPitch(90);



    for (it = objects.begin(); it != end; it++) {
        GLMeshData & mesh = it->second->data;
        if (mesh.compiled == false) continue;
        //std::cout << it->first << ": " << mesh.vboData <<  " - " << mesh.vertices << "\n";
        frame.addPacket(new GLRender(mesh));
    }
    frames.try_push(frame);
}
