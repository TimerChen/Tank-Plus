#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "Operation.h"
#include "Point.h"
#include "Info.h"

namespace TankPlus
{

class Player
{
protected:
	int id, group, money;
	Tank tank;
    Operation *op;
    Info *info;
public:
	Player(Info *info, Operation *operation);
	PlayerInfo to_info(const Point &pos);
};

}

#endif // PLAYER_H
