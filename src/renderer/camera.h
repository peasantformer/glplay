#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    glm::mat4 getMVP(float width, float height) const;
    glm::vec3 getFacingDirection();

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
    static const glm::vec4 baseDirection;
    static const glm::vec4 upBaseDirection;

    glm::vec3 direction;

    float near;
    float far;
    float fov;
    float roll;
    float pitch;
    float yaw;
};

#endif // CAMERA_H
