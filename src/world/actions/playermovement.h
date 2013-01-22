#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

#include <src/world/actions/worldaction.h>

#include <glm/glm.hpp>

class PlayerMovement : public WorldAction
{
public:
    PlayerMovement(glm::vec3 direction);
    virtual ~PlayerMovement();
    virtual void visit(World &world);
};

#endif // PLAYERMOVEMENT_H
