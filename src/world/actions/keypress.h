#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <src/world/actions/worldaction.h>

class KeyPress : public WorldAction
{
public:
    int key;
    int state;

    KeyPress(int key, int state);
    virtual ~KeyPress();
    virtual void visit(World &world);
};

#endif // KEYPRESS_H
