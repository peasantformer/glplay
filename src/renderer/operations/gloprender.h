#ifndef GLOPRENDER_H
#define GLOPRENDER_H

#include <src/renderer/shaderprogram.h>
#include <src/renderer/gloperation.h>

#include <glm/glm.hpp>

#include <vector>
#include <functional>

class GLOPRender : public GLOperation
{
public:
    GLOPRender();

    unsigned int vboData;
    unsigned int vboIndices;
    unsigned int vertices;

    glm::vec3 scale;
    glm::vec3 rotateAxis;
    float     rotateAngle;
    glm::vec3 translation;
    glm::mat4 parentModel;

    unsigned int shaderProgram;

    //std::vector<unsigned int> shaderObjects;
    std::function<void(ShaderProgram const&)> shaderPopulatorCallback;

    void visit(Renderer &renderer);

};

#endif // GLOPRENDER_H
