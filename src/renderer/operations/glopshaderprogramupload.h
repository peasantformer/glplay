#ifndef GLOPSHADERPROGRAMUPLOAD_H
#define GLOPSHADERPROGRAMUPLOAD_H

#include <src/renderer/operations/glopupload.h>

#include <vector>

class GLOPShaderProgramUpload : public GLOPUpload
{
public:
    GLOPShaderProgramUpload();

    std::vector<unsigned int> objects;
    std::function<void(unsigned int)> callback;

    void markUploaded(unsigned int programId);
    void visit(Renderer &renderer);
};

#endif // GLOPSHADERPROGRAMUPLOAD_H
