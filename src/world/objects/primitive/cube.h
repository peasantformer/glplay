#ifndef CUBE_H
#define CUBE_H

#include <src/world/bases/prop.h>

class Cube : public Prop
{
public:
    Cube(std::string const& name, Space const& space, glm::vec3 const& dimensions);
    virtual ~Cube();

protected:
    virtual void populateData(GLMeshSource &source);
    virtual std::string genCacheKey();
private:
    glm::vec3 const& dimensions;
};

#endif // CUBE_H
