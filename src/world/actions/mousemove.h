#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include <src/world/actions/worldaction.h>

class MouseMove : public WorldAction
{
public:
    int x;
    int y;

    MouseMove(int x, int y);
    virtual ~MouseMove();
    virtual void visit(World &world);
};

#endif // MOUSEMOVE_H
