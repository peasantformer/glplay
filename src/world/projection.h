#ifndef PROJECTION_H
#define PROJECTION_H

#include <src/world/rotations.h>

#include <glm/glm.hpp>

class Projection
{
public:
    Projection();

    glm::vec3 position;
    glm::vec3 scale;
    Rotations rotations;
};

#endif // PROJECTION_H
