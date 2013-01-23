#include "keypress.h"

#include <src/world/world.h>

KeyPress::KeyPress(int key, int state)
    : key(key)
    , state(state)
{
}

KeyPress::~KeyPress()
{
}

void KeyPress::visit(World &world)
{
    world.action(*this);
}
