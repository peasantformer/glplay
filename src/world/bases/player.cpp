#include "player.h"

Player::Player(const std::string &name)
    : Base(name)
{
}

Player::Player(const std::string &name, const Space &space)
    : Base(name, space)
{
}

Player::~Player()
{
}
