#include "engine.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

#include <src/world/actions/keypress.h>
#include <src/world/actions/mousemove.h>
#include <src/world/bases/prop.h>

#include <src/renderer/packets/glcompilegeometry.h>
#include <src/renderer/packets/glcompileshader.h>
#include <src/renderer/renderer.h>
#include <src/world/world.h>

#include <iostream>
#include <memory>
#include <iomanip>

static Engine * engineStatic = 0;

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

Engine::Engine(std::shared_ptr<Renderer> renderer, std::shared_ptr<World> world)
    : GameThread(30)
    , renderer(*renderer)
    , world(*world)
    , t_engine(std::ref(*this))
    , t_renderer(std::ref(*renderer))
    , t_world(std::ref(*world))
{
    engineStatic = this;
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

void Engine::addPlayer(std::shared_ptr<Player> player)
{
    world.addPlayer(player);
}



void Engine::addProp(std::shared_ptr<Prop> prop)
{
    if (compileRenderable(prop)) {
        world.addProp(prop);
    } else {
        stop();
    }
}

void Engine::keyFunStatic(GLFWwindow *win, int key, int state)
{
    engineStatic->keyFun(key,state);
}

void Engine::cursorFunStatic(GLFWwindow *win, int x, int y)
{
    engineStatic->cursorFun(x,y);
}

void Engine::keyFun(int key, int state)
{
    world.addAction(std::shared_ptr<WorldAction>(new KeyPress(key,state)));
}

void Engine::cursorFun(int x, int y)
{
    world.addAction(std::shared_ptr<WorldAction>(new MouseMove(x,y)));
}

void Engine::setEngine(Engine *e)
{
    engineStatic = e;
}

void Engine::init()
{
    setEngine(this);
    world.setEngine(this);
    renderer.setEngine(this);

    renderer.waitForInit();
    world.waitForInit();
    glfwSetCursorPos(renderer.getWindow(),renderer.getWidth()/2,renderer.getHeight()/2);
    glfwSetInputMode(renderer.getWindow(),GLFW_CURSOR_MODE,GLFW_CURSOR_CAPTURED);
    glfwSetKeyCallback(renderer.getWindow(),keyFunStatic);
    glfwSetCursorPosCallback(renderer.getWindow(),cursorFunStatic);
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

bool Engine::compileRenderable(std::shared_ptr<Renderable> renderable)
{
    GLMeshSource const& source  = renderable->loadData();

    GLFrame frame;
    std::shared_ptr<GLCompileGeometry> geometryCompiler(new GLCompileGeometry(source));
    std::shared_ptr<GLCompileShader> shaderCompiler(new GLCompileShader(source));
    frame.addPacket(geometryCompiler);
    frame.addPacket(shaderCompiler);

    geometryCompiler->callback = [&renderable](unsigned int d, unsigned int v, unsigned int vs) {
        renderable->data.vboData = d;
        renderable->data.vboIndices = v;
        renderable->data.vertices = vs;
        renderable->data.compiled = true;

    };

    bool errorState = false;

    shaderCompiler->callback = [&errorState,&renderable](unsigned int prog, std::string const& messages) {
        if (!messages.empty()) {
            std::cout << messages << std::endl;
            errorState = true;
        } else {
            renderable->data.shaderProgram = prog;
        }
    };


    renderer.pushFrameWait(frame);

    shaderCompiler->wait();
    geometryCompiler->wait();

    if (errorState) {
        renderable->data.vboData = 0;
        renderable->data.vboIndices = 0;
        renderable->data.vertices = 0;
        return false;
    } else {
        return true;
    }
}

