#ifndef GLOPSHADERUPLOAD_H
#define GLOPSHADERUPLOAD_H

#include <src/renderer/operations/glopupload.h>

#include <string>
#include <functional>

class GLOPShaderUpload : public GLOPUpload
{
public:
    enum ShaderType {
        Vertex,
        Fragment
    };

    GLOPShaderUpload(ShaderType type);
    ShaderType type;
    std::string source;
    std::function<void(unsigned int, std::string const&)> callback;

    void markUploaded(unsigned int objectId, std::string const& resultMessage);
    void visit(Renderer &renderer);
};

#endif // GLOPSHADERUPLOAD_H
