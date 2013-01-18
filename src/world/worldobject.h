#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <src/renderer/operations/gloprender.h>

#include <glm/glm.hpp>

#include <map>
#include <string>

class WorldObject
{
public:
    WorldObject();

    glm::vec3 scale;
    glm::vec3 rotateAxis;
    float     rotateAngle;
    glm::vec3 translation;

    std::map<std::string, std::shared_ptr<GLOPRender> > meshes;
};

#endif // WORLDOBJECT_H
