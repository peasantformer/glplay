#include "engine.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>


#include <src/world/objects/worldobject.h>
#include <src/renderer/packets/glcompilegeometry.h>
#include <src/renderer/packets/glcompileshader.h>
#include <src/renderer/renderer.h>
#include <src/world/world.h>

#include <iostream>
#include <memory>
#include <iomanip>

Engine::Engine(Renderer &renderer, World &world)
    : GameThread(30)
    , renderer(renderer)
    , world(world)
    , t_engine(std::ref(*this))
    , t_renderer(std::ref(renderer))
    , t_world(std::ref(world))
{
    std::cout << "Peasantformer launched\n";
}

Engine::~Engine()
{
    wait();
    std::cout << "Peasantformer quit\n";
}

void Engine::operator ()()
{
    init();
    while (!isDone()) {
        beginTick();

        std::cout << "ENG: " << std::setw(3) << fps()          << "(" << std::setw(8) << time()          << ") | "
                  << "RDR: " << std::setw(3) << renderer.fps() << "(" << std::setw(8) << renderer.time() << ") | "
                  << "WRD: " << std::setw(3) << world.fps()    << "(" << std::setw(8) << world.time()    << ")\n";

        exchangeObjects();
        endTick();
    }
    deinit();
}

void Engine::wait()
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

void Engine::addObject(WorldObject *object)
{
    addObject(std::shared_ptr<WorldObject>(object));
}

void Engine::addObject(std::shared_ptr<WorldObject> object)
{
    GLMeshSource const& source = object->loadData();

    GLFrame frame;
    std::shared_ptr<GLCompileGeometry> geometryCompiler(new GLCompileGeometry(source));
    std::shared_ptr<GLCompileShader> shaderCompiler(new GLCompileShader(source));
    frame.addPacket(geometryCompiler);
    frame.addPacket(shaderCompiler);

    geometryCompiler->callback = [&object](unsigned int d, unsigned int v, unsigned int vs) {
        object->data.vboData = d;
        object->data.vboIndices = v;
        object->data.vertices = vs;
        object->data.compiled = true;

    };

    bool errorState = false;

    shaderCompiler->callback = [&errorState,&object](unsigned int prog, std::string const& messages) {
        if (!messages.empty()) {
            std::cout << messages << std::endl;
            errorState = false;
        } else {
            object->data.shaderProgram = prog;
        }
    };


    renderer.pushFrameWait(frame);

    shaderCompiler->wait();
    geometryCompiler->wait();

    if (errorState) {
        object->data.vboData = 0;
        object->data.vboIndices = 0;
        object->data.vertices = 0;
        return;
    } else {
        world.addObject(object);
    }
}

void Engine::init()
{
    renderer.waitForInit();
    world.waitForInit();
    glfwSetCursorPos(renderer.getWindow(),-1,-1);
    glfwSetInputMode(renderer.getWindow(),GLFW_CURSOR_MODE,GLFW_CURSOR_CAPTURED);
    initNotify();

}

void Engine::deinit()
{
    world.stop();
    renderer.stop();
}

void Engine::exchangeObjects()
{
    GLFrame frame;

    if (world.getFrame(frame)) {
        renderer.pushFrame(frame);
    }
}

