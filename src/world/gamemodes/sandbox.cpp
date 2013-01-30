#include "sandbox.h"

#include <src/world/bases/player.h>
#include <src/world/bases/prop.h>

#include <src/world/actions/keypress.h>
#include <src/world/actions/mousemove.h>
#include <src/world/actions/worldaction.h>

#include <src/engine/engine.h>

#include <src/renderer/packets/glrender.h>

#include <GL/glfw3.h>

#include <iostream>

Sandbox::Sandbox()
    : oldMousePos(-1.0f, -1.0f)
{
}

Sandbox::~Sandbox()
{
}

void Sandbox::action(KeyPress &action)
{
    pressedKeys[action.key] = (action.state == GLFW_PRESS);
}

void Sandbox::action(MouseMove &action)
{
    WorldContainer<Player>::iterator it,end;
    end = players.end();
    it = players.begin();

    if (it != end) {
        std::shared_ptr<Player> player = it->second;
        Space & space = player->space;
        Space & disposition = player->disposition;

        glm::vec2 angle(action.x, action.y);
        glm::vec2 tmp = (oldMousePos - angle) * playerAngularSpeed;

        if (oldMousePos != glm::vec2(-1.0f, -1.0f)) {
            disposition.rotate(tmp.x, glm::vec3(0.0f, -1.0f, 0.0f));
            disposition.rotate(tmp.y, glm::vec3(-1.0f, 0.0f, 0.0f));
        }

        oldMousePos = angle;
    }
}

void Sandbox::init()
{
    playerLinearSpeed = 0.2f;
    playerAngularSpeed = 0.1f;
    initNotify();
}

void Sandbox::deinit()
{
}

void Sandbox::processNewObjects()
{
    std::shared_ptr<Player> player;
    std::shared_ptr<Prop> prop;

    while (players.newObjects.try_pop(player)) {
        players.objects[player->name] = player;
    }

    while (props.newObjects.try_pop(prop)) {
        props.objects[prop->name] = prop;
    }
}

void Sandbox::processActions()
{
    std::shared_ptr<WorldAction> action;
    while (actions.try_pop(action)) {
        action->visit(*this);
    }
}

void Sandbox::evaluateWorld()
{
    handleKeys();

    WorldContainer<Player>::iterator it,end;
    end = players.end();
    for (it = players.begin(); it != end; it++) {
        std::shared_ptr<Player> player = it->second;
        Space & space = player->space;
        Space & disposition = player->disposition;

        if (glm::length(disposition.getTranslation()) != 0.0f) {
            space.translate(glm::normalize(disposition.getTranslation()) * playerLinearSpeed);
        }

        space.rotationQuat = disposition.rotationQuat * space.rotationQuat;

        disposition = Space();
    }
}

void Sandbox::selectObjectsToRender()
{
    if (frames.full()) return;

    GLFrame frame;

    WorldContainer<Player>::iterator pit,pend;
    pend = players.end();
    pit = players.begin();

    if (pit != pend) {
        frame.camera.space = pit->second->space;
    }


    WorldContainer<Prop>::iterator prop_it, prop_end;
    prop_end = props.end();

    for (prop_it = props.begin(); prop_it != prop_end; prop_it++) {
        GLMeshData & mesh = prop_it->second->data;
        if (mesh.compiled == false) continue;
        frame.addPacket(new GLRender(mesh));
    }

    frames.try_push(frame);
}

void Sandbox::handleKeys()
{
    WorldContainer<Player>::iterator it,end;
    end = players.end();
    it = players.begin();

    if (it != end) {
        std::shared_ptr<Player> player = it->second;
        Space & space = player->space;
        Space & disposition = player->disposition;

        if (pressedKeys[GLFW_KEY_ESC]) {
            engine->stop();
        }

        if (pressedKeys[GLFW_KEY_W]) {
            disposition.translate(space.getForwardDirection());
        }

        if (pressedKeys[GLFW_KEY_A]) {
            disposition.translate(space.getSideDirection() * -1.0f);
        }

        if (pressedKeys[GLFW_KEY_S]) {
            disposition.translate(space.getForwardDirection() * -1.0f);
        }

        if (pressedKeys[GLFW_KEY_D]) {
            disposition.translate(space.getSideDirection());
        }

        if (pressedKeys[GLFW_KEY_SPACE]) {
            disposition.translate(space.getUpDirection());
        }

        if (pressedKeys[GLFW_KEY_C]) {
            disposition.translate(space.getUpDirection() * -1.0f);
        }

        if (pressedKeys[GLFW_KEY_Q]) {
            disposition.rotate(1.0f, glm::vec3(0.0f, 0.0f, -1.0f));
        }
        if (pressedKeys[GLFW_KEY_E]) {
            disposition.rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    }
}
