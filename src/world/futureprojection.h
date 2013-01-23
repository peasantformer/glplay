#ifndef FUTUREPROJECTION_H
#define FUTUREPROJECTION_H

#include <src/world/projection.h>

class FutureProjection
{
public:
    FutureProjection();

    Projection getAndFlush();

    void setSpeed(float value);
    void setDirection(glm::vec3 direction);
    void addDirection(glm::vec3 direction);
    void setPosition(glm::vec3 position);
    void setPitch(float angle);
    void setRoll(float angle);
    void setYaw(float angle);
    void addPitch(float angle);
    void addRoll(float angle);
    void addYaw(float angle);

private:
    Projection projection;
};

#endif // FUTUREPROJECTION_H
