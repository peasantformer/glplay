#ifndef GLOPSHADERBATCHUPLOAD_H
#define GLOPSHADERBATCHUPLOAD_H

#include <src/renderer/operations/glopupload.h>
#include <src/renderer/operations/glopshaderupload.h>

#include <vector>
#include <string>


class GLOPShaderBatchUpload : public GLOPUpload
{
public:
    GLOPShaderBatchUpload();
    std::vector<std::shared_ptr<GLOPShaderUpload> > shaders;
    std::vector<unsigned int> objects;
    std::function<void(unsigned int, std::string const&)> callback;

    void markUploaded(unsigned int programId, std::string const& messages);
    void visit(Renderer &renderer);
};

#endif // GLOPSHADERBATCHUPLOAD_H
