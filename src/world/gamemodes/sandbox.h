#ifndef SANDBOX_H
#define SANDBOX_H

#include <src/world/world.h>

class Sandbox : public World
{
public:
    Sandbox();
    virtual ~Sandbox();

    virtual void action(KeyPress  & action);
    virtual void action(MouseMove & action);

    virtual void init();
    virtual void deinit();
    virtual void processNewObjects();
    virtual void processActions();
    virtual void evaluateWorld();
    virtual void selectObjectsToRender();

private:
    float playerLinearSpeed;
    float playerAngularSpeed;
    std::map<int,bool> pressedKeys;
    glm::vec2 oldMousePos;

    void handleKeys();
};

#endif // SANDBOX_H
