#ifndef PLAYER_HUMAN_H
#define PLAYER_HUMAN_H

#include "Player.h"
namespace GAME
{
class Player_human: public Player
{
public:
    Player_human(const Info *info, Operation *operation);
    void run();
};
}

#endif // PLAYER_HUMAN_H
