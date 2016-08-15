#include "Player.h"

namespace GAME
{

Player::Player(const std::string &name, const Info *info, Operation *operation)
{
    this->name = name;
    this->info = info;
    this->op = operation;
}

}
