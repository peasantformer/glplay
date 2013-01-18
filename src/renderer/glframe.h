#ifndef GLFRAME_H
#define GLFRAME_H

#include <src/renderer/camera.h>

#include <vector>
#include <memory>

class GLOperation;

struct GLFrame
{
public:
    Camera camera;
    std::vector<std::shared_ptr<GLOperation> > operations;
};

#endif // GLFRAME_H
