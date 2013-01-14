#include <src/renderer/renderer.h>
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

    Engine engine(renderer);

    engine.waitTillFinish();

    return 0;
}
