#include "renderer.h"

#include <src/renderer/packets/glrender.h>
#include <src/renderer/packets/glcompilegeometry.h>
#include <src/renderer/packets/glcompileshader.h>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

Renderer::Renderer(int width, int height)
    : width(width)
    , height(height)
    , window(0)
    , queue(2)
{
}

unsigned int Renderer::maxShaderLogLength = 1024;

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

GLFWwindow *Renderer::getWindow()
{
    return window;
}

void Renderer::render(const GLRender &glr)
{
    if (glr.data.shaderProgram != 0) {
        glUseProgram(glr.data.shaderProgram);
        ShaderProgram program(glr.data.shaderProgram);
        program.setUniform("MVP",MVPmatrix * glr.data.model);

        if (glr.data.shaderPopulator) {
            glr.data.shaderPopulator(program);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, glr.data.vboData);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glr.data.vboIndices);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT,   sizeof(float)*8, (float*)(sizeof(float)*0));
    glTexCoordPointer(2, GL_FLOAT, sizeof(float)*8, (float*)(sizeof(float)*3));
    glNormalPointer(GL_FLOAT,      sizeof(float)*8, (float*)(sizeof(float)*5));

    glDrawElements(GL_TRIANGLES, glr.data.vertices, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if (glr.data.shaderProgram != 0) {
        glUseProgram(0);
    }
}


void Renderer::compile(GLCompileGeometry &glc)
{
    unsigned int d = 0;
    unsigned int v = 0;

    unsigned int dataSize = glc.data.size() * sizeof(float);
    unsigned int verticesSize = glc.vertices.size() * sizeof(unsigned int);

    glGenBuffers(1, &d);
    glBindBuffer(GL_ARRAY_BUFFER, d);
    glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, glc.data.data());

    glGenBuffers(1,&v);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, verticesSize, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, verticesSize, glc.vertices.data());

    glc.compiled(d,v,glc.vertices.size());
}

void Renderer::compile(GLCompileShader &glc)
{
    unsigned int prog = 0;

    std::vector<unsigned int> objects;

    unsigned int size = glc.shaderSources.size();

    std::string errorMessages;

    for (int i=0; i < size; i++) {
        unsigned int object;
        GLCompileShader::ShaderSource source = glc.shaderSources[i];

        switch (source.getType()) {
        case GLCompileShader::Vertex:
            object = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GLCompileShader::Fragment:
            object = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        }

        const char * code = source.getSource().data();

        glShaderSource(object, 1, &code, 0);
        glCompileShader(object);

        int logLength = 0;
        char rawLog[maxShaderLogLength];

        glGetShaderInfoLog(object, maxShaderLogLength, &logLength, rawLog);

        if (logLength > 0) {
            if (!errorMessages.empty()) {
                errorMessages.append("\n\n");
            }
            errorMessages.append(rawLog);
        } else {
            objects.push_back(object);
        }
    }

    size = objects.size();

    if (size > 0) {
        prog = glCreateProgram();

        for (int i = 0; i < size; i++) {
            glAttachShader(prog,objects[i]);
        }

        glLinkProgram(prog);
    }

    glc.compiled(prog,errorMessages);
}

void Renderer::pushFrame(GLFrame frame)
{
    queue.try_push(frame);
}

void Renderer::pushFrameWait(GLFrame frame)
{
    queue.wait_and_push(frame);
}


void Renderer::init()
{
    if (!glfwInit()) {
        std::cout << "Renderer initalization failure\n";
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(width, height, "Peasantformer", 0, 0);

    if (!window) {
        std::cout << "Window creation failure\n";
        exit(EXIT_FAILURE);
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

void Renderer::processFrame(GLFrame &frame)
{
    MVPmatrix = frame.camera.getMVP(width,height);

    unsigned int size = frame.packets.size();

    for (unsigned int i = 0; i < size; i++) {
        frame.packets[i]->visit(*this);
    }

}

