#ifndef SPACE_H
#define SPACE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Space
{
public:
    Space(float yaw, float roll, float pitch);
    Space(glm::vec3 const& position);
    Space(glm::vec3 const& position, float yaw, float roll, float pitch);
    Space();

    Space & operator*(Space const& rhs);

    void translate(glm::vec3 const& translation);
    void rotate(float angle, glm::vec3 const& axis);
    void scale(glm::vec3 const& axis);

    glm::vec3 getForwardDirection();
    glm::vec3 getSideDirection();
    glm::vec3 getUpDirection();

    glm::vec3 getTranslation();

    void setOrientation(float yaw = 0.0f, float roll = 0.0f, float pitch = 0.0f);

    glm::mat4 getMatrix() const;

    glm::quat rotationQuat;
    glm::mat4 transformMat;
};

#endif // SPACE_H
