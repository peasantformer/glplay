#include "optionparser.h"

#include <src/world/objects/playercamera.h>
#include <src/world/objects/sademosquare.h>

#include <src/renderer/renderer.h>
#include <src/world/world.h>
#include <src/engine/engine.h>

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

    std::shared_ptr<PlayerCamera> camera(new PlayerCamera("Player"));

    camera->projection.position = glm::vec3(0.0f, 10.0f, 0.0f);
    camera->projection.rotations.pitch = 90.0f;

    engine.addObject(camera);
    engine.addObject(new SadEmoSquare("SadEmoSquare", 1.0f, 1.0f, 1.0f));

    return 0;
}
