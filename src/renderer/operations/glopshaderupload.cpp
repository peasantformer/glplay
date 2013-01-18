#include "glopshaderupload.h"

#include <src/renderer/renderer.h>

GLOPShaderUpload::GLOPShaderUpload(GLOPShaderUpload::ShaderType type)
    : type(type)
{
}

void GLOPShaderUpload::markUploaded(unsigned int objectId, const std::string &resultMessage)
{
    if (callback) {
        callback(objectId, resultMessage);
    }
    doneNotify();
}

void GLOPShaderUpload::visit(Renderer &renderer)
{
    renderer.accept(*this);
}
