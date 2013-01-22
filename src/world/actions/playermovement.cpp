#include "playermovement.h"

#include <src/world/world.h>

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::visit(World &world)
{
    world.move(*this);

}
