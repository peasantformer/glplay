#include "engine.h"

#include <src/renderer/operations/gloprender.h>
#include <src/renderer/operations/glopupload.h>
#include <src/renderer/renderer.h>

#include <src/util/fileutils.h>
#include <src/world/world.h>

#include <iostream>
#include <iomanip>

static Engine * engineStatic = 0;

Engine::Engine(Renderer &renderer, World &world)
    : GameThread(30)
    , renderer(renderer)
    , world(world)
    , t_engine(std::ref(*this))
    , t_renderer(std::ref(renderer))
    , t_world(std::ref(world))
    , listenPointer(true)
{
    engineStatic = this;
}

Engine::~Engine()
{
    waitTillFinish();
    engineStatic = 0;
    std::cout << "Peasantformer quit\n";
}

void Engine::operator ()()
{
    init();

    GLFrame frame;

    std::shared_ptr<GLOPGeometryUpload> dataUpload(new GLOPGeometryUpload());
    dataUpload->data.resize(8*3,0);
    dataUpload->indices.resize(3,0);

    dataUpload->data[0+8*0] =  0;
    dataUpload->data[1+8*0] =  0;
    dataUpload->data[2+8*0] =  1;

    dataUpload->data[0+8*1] =  1;
    dataUpload->data[1+8*1] =  0;
    dataUpload->data[2+8*1] = -1;

    dataUpload->data[0+8*2] = -1;
    dataUpload->data[1+8*2] =  0;
    dataUpload->data[2+8*2] = -1;

    dataUpload->indices[0] = 0;
    dataUpload->indices[1] = 1;
    dataUpload->indices[2] = 2;

    unsigned int vboData = 0;
    unsigned int vboInd  = 0;

    dataUpload->callback = [&vboData, &vboInd](unsigned int d, unsigned int i) {
        vboData = d;
        vboInd  = i;
    };

    unsigned int objectId;

    std::shared_ptr<GLOPShaderUpload> shaderUpload(new GLOPShaderUpload(GLOPShaderUpload::Vertex));
    shaderUpload->source = FileUtils::readToString("baka.vtx");
    shaderUpload->callback = [&objectId](unsigned int id, std::string const& message) {
        std::cout << message << "\n";
        if (!message.empty()) {
            exit(1);
        }
        objectId = id;
    };


    frame.operations.push_back(dataUpload);
    frame.operations.push_back(shaderUpload);
    renderer.pushFrame(frame);
    dataUpload->waitForUpload();
    shaderUpload->waitForUpload();

    Camera camera;

    int pointerX_new = -1;
    int pointerY_new = -1;

    GLFrame renderFrame;

    int size = 2;

    for (int n = -size; n <= size; n++) {

        for (int i = -size; i <= size; i++) {
            std::shared_ptr<GLOPRender> renderOp(new GLOPRender());

            renderOp->vboData = vboData;
            renderOp->vboIndices = vboInd;
            renderOp->vertices = 3;
            renderOp->translation.y = 5*i;
            renderOp->translation.x = 5*n;

            renderOp->shaderObjects.push_back(objectId);

            renderFrame.operations.push_back(renderOp);

        }
    }


    while (!isDone()) {
        beginTick();
        std::cout << "ENG: " << std::setw(3) << fps()          << "(" << std::setw(8) << time()          << ") | "
                  << "RDR: " << std::setw(3) << renderer.fps() << "(" << std::setw(8) << renderer.time() << ") | "
                  << "WRD: " << std::setw(3) << world.fps()    << "(" << std::setw(8) << world.time()    << ")\n";

        renderFrame.camera = camera;

        renderer.pushFrame(renderFrame);

        float speed = 0.2f;
        float angular_speed = 0.1f;

        if (glfwGetKey(renderer.getWindow(),GLFW_KEY_ESC) == GLFW_PRESS) {
            stop();
        }

        glm::vec3 facingDirection = camera.getFacingDirection();

        std::cout << facingDirection.x << " " << facingDirection.y << " " << facingDirection.z << " | "
                  << camera.getPitch() << " " << camera.getYaw() << "\n";

        if (glfwGetKey(renderer.getWindow(), GLFW_KEY_W)) {
            camera.translation += facingDirection * speed;
        }

        if (glfwGetKey(renderer.getWindow(), GLFW_KEY_S)) {
            camera.translation -= facingDirection * speed;
        }


        if (glfwGetKey(renderer.getWindow(), GLFW_KEY_SPACE)) {
            camera.translation.z += speed;
        }

        if (glfwGetKey(renderer.getWindow(), GLFW_KEY_C)) {
            camera.translation.z -= speed;
        }

        glfwGetCursorPos(renderer.getWindow(),&pointerX_new, &pointerY_new);

        if (listenPointer) {
            camera.shiftYaw((float)(pointerX_new - pointerX) * angular_speed);
            camera.shiftPitch((float)(pointerY_new - pointerY) * angular_speed);

            pointerX = pointerX_new;
            pointerY = pointerY_new;
        }

        endTick();
    }
    deinit();
}


void Engine::waitTillFinish()
{
    if (t_renderer.joinable()) {
        t_renderer.join();
    }
    if (t_world.joinable()) {
        t_world.join();
    }
    if (t_engine.joinable()) {
        t_engine.join();
    }
}

void Engine::resetPointer()
{
    pointerX = -1;
    pointerY = -1;
}

void Engine::setListenPointer(bool value)
{
    listenPointer = value;
}

void Engine::cursorEnter(GLFWwindow * window, int entered)
{
    std::cout << "ALR\n";
    if (entered == GL_TRUE) {
        engineStatic->setListenPointer(true);
    } else {
        engineStatic->setListenPointer(false);
    }
    engineStatic->resetPointer();
}

void Engine::init()
{
    renderer.waitForInit();
    world.waitForInit();
    resetPointer();
    glfwSetCursorPos(renderer.getWindow(),-1,-1);
    glfwSetCursorEnterCallback(renderer.getWindow(),Engine::cursorEnter);
    glfwSetInputMode(renderer.getWindow(),GLFW_CURSOR_MODE,GLFW_CURSOR_CAPTURED);
    initNotify();
}

void Engine::deinit()
{
    world.stop();
    renderer.stop();
}
