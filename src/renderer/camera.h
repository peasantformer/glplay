#ifndef CAMERA_H
#define CAMERA_H

#include <src/world/projection.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    glm::mat4 getMVP(float width, float height) const;
    glm::vec3 getFacingDirection();
    glm::vec3 getUpDirection();

    void setProjection(Projection & projection);

    glm::vec3 translation;
    void shiftNear(float value);
    void shiftFar(float value);
    void shiftFov(float value);
    void shiftRoll(float value);
    void shiftPitch(float value);
    void shiftYaw(float value);

    void setNear(float value);
    void setFar(float value);
    void seFov(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);

    float getNear();
    float getFar();
    float getFov();
    float getRoll();
    float getPitch();
    float getYaw();

private:
    glm::vec3 extractVec3FromVec4(glm::vec4 const& source) const;
    glm::mat4 cameraMat;

    float near;
    float far;
    float fov;
    float roll;
    float pitch;
    float yaw;
};

#endif // CAMERA_H
