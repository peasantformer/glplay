#include "mousemove.h"

#include <src/world/world.h>

MouseMove::MouseMove(int x, int y)
    : x(x)
    , y(y)
{
}

MouseMove::~MouseMove()
{
}

void MouseMove::visit(World &world)
{
    world.action(*this);
}
