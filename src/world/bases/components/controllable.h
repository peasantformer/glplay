#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include <src/world/space.h>

class Controllable
{
public:
    virtual ~Controllable();

    Space disposition;
};

#endif // CONTROLLABLE_H
