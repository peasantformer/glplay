#ifndef GLOPGEOMETRYUPLOAD_H
#define GLOPGEOMETRYUPLOAD_H

#include <src/renderer/operations/glopupload.h>

#include <vector>
#include <functional>

class GLOPGeometryUpload : public GLOPUpload
{
public:
    std::vector<float> data;
    std::vector<unsigned int> indices;
    std::function<void(unsigned int, unsigned int)> callback;

    void markUploaded(unsigned int dataId, unsigned int idxId);
    void visit(Renderer &renderer);
};

#endif // GLOPGEOMETRYUPLOAD_H
