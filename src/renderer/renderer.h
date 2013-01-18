#ifndef RENDERER_H
#define RENDERER_H

#include <src/renderer/glframe.h>
#include <src/renderer/gloperation.h>
#include <src/renderer/operations/glopupload.h>
#include <src/renderer/operations/glopgeometryupload.h>
#include <src/renderer/operations/glopshaderupload.h>
#include <src/renderer/operations/gloprender.h>

#include <src/util/blockingqueue.h>

#include <src/base/gamethread.h>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

class GLFWwindow;

class Renderer : public GameThread
{
public:
    Renderer(int width, int height);
    virtual ~Renderer();

    void operator()();

    GLFWwindow * getWindow() const;

    void accept(GLOperation & op);
    void accept(GLOPUpload & op);
    void accept(GLOPGeometryUpload & op);
    void accept(GLOPShaderUpload & op);
    void accept(GLOPRender & op);

    void pushFrame(GLFrame const& frame);

private:
    void init();
    void deinit();
    void processFrame(GLFrame const& frame);

    int width;
    int height;
    glm::mat4 MVP;

    BlockingQueue<GLFrame> queue;

    GLFWwindow * window;
};

#endif // RENDERER_H
