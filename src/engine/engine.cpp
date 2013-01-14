#include "engine.h"

#include <src/renderer/renderer.h>

#include <iostream>
#include <iomanip>

Engine::Engine(Renderer &renderer)
    : GameThread(30)
    , renderer(renderer)
    , t_engine(std::ref(*this))
    , t_renderer(std::ref(renderer))
{
    renderer.waitForInit();
}

Engine::~Engine()
{
    waitTillFinish();
}

void Engine::operator ()()
{
    init();
    done = false;

    while (!done) {
        beginTick();
        std::cout << "ENG: " << std::setw(3) << fps()          << "(" << std::setw(8) << time()          << ") | "
                  << "RDR: " << std::setw(3) << renderer.fps() << "(" << std::setw(8) << renderer.time() << ")\n";

        endTick();
    }
}


void Engine::waitTillFinish()
{
    t_renderer.join();
}

void Engine::init()
{
    initNotify();
}
