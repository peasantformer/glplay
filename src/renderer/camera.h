#ifndef CAMERA_H
#define CAMERA_H

//#include <src/world/projection.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <src/world/space.h>

class Camera
{
public:
    Space space;

    Camera();
    virtual ~Camera();
    glm::mat4 getMVP(float width, float height) const;

    void shiftNear(float value);
    void shiftFar(float value);
    void shiftFov(float value);

    void setNear(float value);
    void setFar(float value);
    void seFov(float value);

    float getNear();
    float getFar();
    float getFov();

private:
    float near;
    float far;
    float fov;
};

#endif // CAMERA_H
