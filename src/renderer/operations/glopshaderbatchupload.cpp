#include "glopshaderbatchupload.h"

#include <src/renderer/renderer.h>

GLOPShaderBatchUpload::GLOPShaderBatchUpload()
{
}

void GLOPShaderBatchUpload::markUploaded(unsigned int programId, std::string const& messages)
{
    if (callback) {
        callback(programId, messages);
    }
    doneNotify();
}

void GLOPShaderBatchUpload::visit(Renderer &renderer)
{
    renderer.accept(*this);
}


