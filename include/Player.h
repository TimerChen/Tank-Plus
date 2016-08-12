#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "Operation.h"
#include "Point.h"
#include "Info.h"
#include "Item.h"
#include <vector>

namespace GAME
{

class Player
{
public:
	int id, group, money;
	Tank tank;
	std::vector<Item> item;
    Operation *op;
    const Info *info;
	Player(const Info *info, Operation *operation);
	PlayerInfo to_info(const Point &pos);
	virtual void run() = 0;
};

}

#endif // PLAYER_H
