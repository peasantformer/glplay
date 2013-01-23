#ifndef SANDBOXWORLD_H
#define SANDBOXWORLD_H

#include <src/world/world.h>

#include <src/world/objects/playercamera.h>

class SandboxWorld : public World
{
public:
    SandboxWorld();
    virtual ~SandboxWorld();

    virtual void action(KeyPress  & action);
    virtual void action(MouseMove & action);

protected:
    virtual void init();
    virtual void deinit();
    virtual void processNewObjects();
    virtual void processActions();
    virtual void evaluateWorld();
    virtual void selectObjectsToRender();

private:
    int oldMouseX;
    int oldMouseY;
    std::shared_ptr<PlayerCamera> camera;
    float playerSpeed;
    float playerAngularSpeed;
    std::map<int,bool> pressedKeys;
    bool listenMouse;
};

#endif // SANDBOXWORLD_H
