#include <src/renderer/renderer.h>
#include <src/world/world.h>
#include <src/engine/engine.h>

#include "optionparser.h"

#include <iostream>
#include <thread>

#include <unistd.h>

int main(int argc, char ** argv) {
    OptionParser optParser(argc,argv);

    if (!optParser.parse()) {
        return -1;
    }

    chdir(optParser.getWorkingDirectory().c_str());

    Renderer renderer(optParser.getWidth(),optParser.getHeight());
    World world;
    Engine engine(renderer, world);

    engine.waitTillFinish();

    return 0;
}
