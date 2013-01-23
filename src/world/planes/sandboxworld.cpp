#include "sandboxworld.h"

#include <src/world/actions/keypress.h>
#include <src/world/actions/mousemove.h>

#include <src/engine/engine.h>

#include <src/renderer/packets/glrender.h>

#include <GL/glfw3.h>

#include <iostream>

SandboxWorld::SandboxWorld()
    : camera(new PlayerCamera("Player"))
    , listenMouse(true)
{
}

SandboxWorld::~SandboxWorld()
{
}

void SandboxWorld::action(KeyPress &action)
{
    pressedKeys[action.key] = (action.state == GLFW_PRESS);
}

void SandboxWorld::action(MouseMove &action)
{
    if (listenMouse) {
        camera->futureProjection.addYaw((oldMouseX - action.x) * playerAngularSpeed);
        camera->futureProjection.addPitch((oldMouseY - action.y) * -playerAngularSpeed);

        oldMouseX = action.x;
        oldMouseY = action.y;
    }
    //camera->futureProjection
}

void SandboxWorld::init()
{
    playerSpeed = 0.2f;
    playerAngularSpeed = 0.1f;
    oldMouseX = -1;
    oldMouseY = -1;
    camera->projection.rotations.yaw = 180.0f;
    camera->projection.rotations.pitch = 90.0f;
    addObject(camera);
    initNotify();
}

void SandboxWorld::deinit()
{
}

void SandboxWorld::processNewObjects()
{
    std::shared_ptr<WorldObject> newObj;
    while (newObjects.try_pop(newObj)) {
        objects[newObj->name] = newObj;
    }
}

void SandboxWorld::processActions()
{
    std::shared_ptr<WorldAction> action;
    while (actions.try_pop(action)) {
        action->visit(*this);
    }
}

void SandboxWorld::evaluateWorld()
{
    if (pressedKeys[GLFW_KEY_ESC]) {
        engine->stop();
    }

    if (pressedKeys[GLFW_KEY_W]) {
        camera->futureProjection.addDirection(camera->getFacingDirection());
    }

    if (pressedKeys[GLFW_KEY_S]) {
        camera->futureProjection.addDirection(camera->getFacingDirection() * -1.0f);
    }

    if (pressedKeys[GLFW_KEY_A]) {
        camera->futureProjection.addDirection(camera->getSideDirection());
    }

    if (pressedKeys[GLFW_KEY_D]) {
        camera->futureProjection.addDirection(camera->getSideDirection() * -1.0f);
    }

    if (pressedKeys[GLFW_KEY_SPACE]) {
        camera->futureProjection.addDirection(camera->getUpDirection());
    }

    if (pressedKeys[GLFW_KEY_C]) {
        camera->futureProjection.addDirection(camera->getUpDirection() * -1.0f);
    }


    std::map<std::string, std::shared_ptr<WorldObject> >::iterator it, end;
    end = objects.end();

    for (it = objects.begin(); it != end; it++) {
        Projection & projection = it->second->projection;
        Projection const& futureProjection = it->second->futureProjection.getAndFlush();

        projection.translation += futureProjection.translation;
        projection.rotations.shift(futureProjection.rotations);
    }
}

void SandboxWorld::selectObjectsToRender()
{
    if (frames.full()) return;

    GLFrame frame;

    //std::cout << camera->projection.translation.x << " " << camera->projection.translation.y << " " << camera->projection.translation.z << "\n";

    frame.camera.setProjection(camera->projection);

    std::map<std::string, std::shared_ptr<WorldObject> >::iterator it, end;
    end = objects.end();

    for (it = objects.begin(); it != end; it++) {
        GLMeshData & mesh = it->second->data;
        if (mesh.compiled == false) continue;
        frame.addPacket(new GLRender(mesh));
    }
    frames.try_push(frame);
}
