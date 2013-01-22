#ifndef RENDERER_H
#define RENDERER_H

#include <src/renderer/glmeshdata.h>

#include <src/renderer/glframe.h>

#include <src/util/blockingqueue.h>

#include <src/base/gamethread.h>

#include <glm/glm.hpp>

#include <memory>
#include <iostream>

class GLFWwindow;

class GLRender;
class GLCompileGeometry;
class GLCompileShader;

class Renderer : public GameThread
{
public:
    Renderer(int width, int height);
    virtual ~Renderer();

    virtual void operator ()();

    GLFWwindow * getWindow();

    void render(GLRender const& glr);

    void compile(GLCompileGeometry & glc);
    void compile(GLCompileShader & glc);

    void pushFrame(GLFrame frame);
    void pushFrameWait(GLFrame frame);

private:
    static unsigned int maxShaderLogLength;
    int width, height;
    glm::mat4 MVPmatrix;
    GLFWwindow * window;
    BlockingQueue<GLFrame> queue;

    void init();
    void deinit();
    void processFrame(GLFrame & frame);
};

#endif // RENDERER_H
