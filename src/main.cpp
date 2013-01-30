#include "optionparser.h"

#include <src/world/objects/primitive/cube.h>
#include <src/world/bases/player.h>

#include <src/world/gamemodes/sandbox.h>

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

    std::shared_ptr<Renderer> renderer(new Renderer(optParser.getWidth(),optParser.getHeight()));
    std::shared_ptr<World> world(new Sandbox());
    Engine engine(renderer, world);

    std::shared_ptr<Player> player(new Player("Player1", Space(glm::vec3(0.0f, -10.0f, 0.0f), 0.0f, 0.0f, 0.0f)));
    std::shared_ptr<Prop> sadEmoSquare(new Cube("SadEmoSquare", Space(), glm::vec3(1.0f, 1.0f, 1.0f)));

    engine.addPlayer(player);
    engine.addProp(sadEmoSquare);

    return 0;
}
