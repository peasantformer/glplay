#include "rotations.h"

Rotations::Rotations()
    : pitch(0)
    , roll(0)
    , yaw(0)
{
}

void Rotations::shift(const Rotations &rhs)
{
    pitch += rhs.pitch;
    roll += rhs.roll;
    yaw += rhs.yaw;
}
