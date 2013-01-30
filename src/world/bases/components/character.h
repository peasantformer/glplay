#ifndef CHARACTER_H
#define CHARACTER_H

#include <src/world/bases/components/animatable.h>
#include <src/world/bases/components/physical.h>
#include <src/world/bases/components/renderable.h>

class Character : public Animatable, public Physical, public Renderable
{
public:
    virtual ~Character();
};

#endif // CHARACTER_H
