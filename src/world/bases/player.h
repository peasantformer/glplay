#ifndef PLAYER_H
#define PLAYER_H

#include <src/world/bases/components/base.h>
#include <src/world/bases/components/controllable.h>
#include <src/world/bases/components/physical.h>

class Player : public Base, public Physical, public Controllable
{
public:
    Player(std::string const& name);
    Player(std::string const& name, Space const& space);
    virtual ~Player();
};

#endif // PLAYER_H
