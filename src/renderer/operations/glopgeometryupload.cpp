#include "glopgeometryupload.h"

#include <src/renderer/renderer.h>

void GLOPGeometryUpload::markUploaded(unsigned int dataId, unsigned int idxId)
{
    if (callback) {
        callback(dataId,idxId);
    }
    doneNotify();
}

void GLOPGeometryUpload::visit(Renderer &renderer)
{
    renderer.accept(*this);
}


