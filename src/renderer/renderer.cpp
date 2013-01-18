#include "renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Renderer::Renderer(int width, int height)
    : GameThread(60)
    , width(width)
    , height(height)
    , queue(2)
{
}

Renderer::~Renderer()
{
}

void Renderer::operator ()()
{
    init();
    GLFrame frame;
    while (!isDone()) {
        beginTick();
        if (queue.try_pop(frame)) {
            glfwPollEvents();
            glfwGetWindowSize(window,&width,&height);

            glViewport(0,0,width,height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            processFrame(frame);
            glfwSwapBuffers(window);
        }
        endTick();
    }
    deinit();
}

GLFWwindow *Renderer::getWindow() const
{
    return window;
}

void Renderer::accept(GLOperation &op)
{
    std::cout << "generic GL operation\n";
}

void Renderer::accept(GLOPUpload &op)
{
    std::cout << "generic GL upload operation\n";
}

void Renderer::accept(GLOPGeometryUpload &op)
{
    unsigned int vboData = 0;
    unsigned int vboIndices = 0;

    unsigned int dataSize = op.data.size()    * sizeof(float);
    unsigned int indSize  = op.indices.size() * sizeof(unsigned int);

    glGenBuffers(1, &vboData);
    glBindBuffer(GL_ARRAY_BUFFER, vboData);
    glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, op.data.data());

    glGenBuffers(1,&vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indSize, op.indices.data());

    op.markUploaded(vboData, vboIndices);
}

void Renderer::accept(GLOPShaderUpload &op)
{
    unsigned int objectId = 0;

    switch (op.type) {
    case GLOPShaderUpload::Vertex:
        objectId = glCreateShader(GL_VERTEX_SHADER);
        break;
    case GLOPShaderUpload::Fragment:
        objectId = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }

    const char * code = op.source.data();

    glShaderSource(objectId, 1, &code, 0);
    glCompileShader(objectId);

    static int maxLogLength = 1024;

    int logLength = 0;
    char rawLog[maxLogLength];
    std::string log;

    glGetShaderInfoLog(objectId, maxLogLength, &logLength, rawLog);

    if (logLength > 0) {
        log.assign(rawLog);
    }

    op.markUploaded(objectId, log);

}

void Renderer::accept(GLOPRender &op)
{
    if (!op.shaderObjects.empty()) {
        unsigned int shaderProgram = glCreateProgram();

        unsigned int size = op.shaderObjects.size();

        for (int i = 0; i < size; i++) {
            glAttachShader(shaderProgram,op.shaderObjects[i]);
        }
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        ShaderProgram program(shaderProgram);

        glm::mat4 model;

        model = glm::scale(model,op.scale);
        // think about this boolean expression, there is got to be a better way to do this
        if (op.rotateAxis.x != 0.0f || op.rotateAxis.y != 0.0f || op.rotateAxis.z != 0.0f) {
            model = glm::rotate(model,op.rotateAngle,op.rotateAxis);
        }
        model = glm::translate(model,op.translation);

        program.setUniform("MVP",MVP * op.parentModel * model);

        if (op.shaderPopulatorCallback) {
            op.shaderPopulatorCallback(program);
        }
    }


    glBindBuffer(GL_ARRAY_BUFFER, op.vboData);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, op.vboIndices);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT,   sizeof(float)*8, (float*)(sizeof(float)*0));
    glNormalPointer(GL_FLOAT,      sizeof(float)*8, (float*)(sizeof(float)*3));
    glTexCoordPointer(3, GL_FLOAT, sizeof(float)*8, (float*)(sizeof(float)*5));

    glDrawElements(GL_TRIANGLES, op.vertices, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}

void Renderer::pushFrame(const GLFrame &frame)
{
    queue.try_push(frame);
}

void Renderer::init()
{
    if (!glfwInit()) {
        std::cout << "Renderer initalization failure\n";
        exit(1);
    }

    window = glfwCreateWindow(width, height, "Peasantformer", 0, 0);

    if (!window) {
        std::cout << "Window creation failure\n";
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glewInit();


    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);


    glfwSwapInterval(0);

    glfwSetTime(0);

    initNotify();
}

void Renderer::deinit()
{
    glfwTerminate();
}
void Renderer::processFrame(GLFrame const& frame)
{
    MVP = frame.camera.getMVP(width, height);

    unsigned int size = frame.operations.size();

    for (unsigned int i = 0; i < size; i++) {
        frame.operations[i]->visit(*this);
    }
}
