#include "optionparser.h"

#include <src/world/objects/primitive/cube.h>
#include <src/world/bases/player.h>

#include <src/world/gamemodes/sandbox.h>

#include <src/renderer/renderer.h>
#include <src/world/world.h>
#include <src/engine/engine.h>

#include <sstream>
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

    std::shared_ptr<Player> player(new Player("Player1", Space(glm::vec3(0.0f, -40.0f, 0.0f), 0.0f, 0.0f, 0.0f)));

    engine.addPlayer(player);

    int size = 5;

    int z = 0;

    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            for (int k = -size; k <= size; k++) {
                std::stringstream ss;
                ss << "SadEmoSquare" << z++;
                std::string name;
                ss >> name;
                std::shared_ptr<Prop> prop(new Cube(name, Space(glm::vec3(i * 2.0f, j * 2.0f, k * 2.0f)), glm::vec3(1.0f, 1.0f, 1.0f)));
                engine.addProp(std::shared_ptr<Prop>(prop));
            }
        }
    }

    //exit(0);

    /*
    WorldContainer<Prop> baka;
    baka.newObjects.try_push(std::shared_ptr<Prop>(new Cube("A", Space(glm::vec3(2.0f, 2.0f, 2.0f)), glm::vec3(1.0f, 1.0f, 1.0f))));
    baka.newObjects.try_push(std::shared_ptr<Prop>(new Cube("B", Space(glm::vec3(2.0f, 2.0f, 2.0f)), glm::vec3(1.0f, 1.0f, 1.0f))));

    std::shared_ptr<Prop> i;

    while (baka.newObjects.try_pop(i)) {
        std::cout << i->name << std::endl;
    }

    exit(0);
    */
    return 0;
}
