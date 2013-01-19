#include "glopshaderprogramupload.h"

#include <src/renderer/renderer.h>

GLOPShaderProgramUpload::GLOPShaderProgramUpload()
{
}

void GLOPShaderProgramUpload::markUploaded(unsigned int programId)
{
    if (callback) {
        callback(programId);
    }
    doneNotify();
}

void GLOPShaderProgramUpload::visit(Renderer &renderer)
{
    renderer.accept(*this);
}
