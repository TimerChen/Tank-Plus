#ifndef PLAYER_AI_H
#define PLAYER_AI_H

#include "Player.h"
namespace GAME
{
class Player_ai: public Player
{
public:
    Player_ai(const std::string &name, const Info *info, Operation *operation);
    void run();
};
}

#endif // PLAYER_AI_H
