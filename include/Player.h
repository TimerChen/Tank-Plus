#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "Operation.h"
#include "Point.h"
#include "Item.h"
#include <vector>

namespace GAME
{
class Battlefield;
class Info;
class PlayerInfo;
class Player
{
public:
    std::string name;
	int id, group, money;
	Tank tank;
	std::vector<Item> item;
    Operation *op;
    const Info *info;
	Player(const std::string &name, const Info *info, Operation *operation);
	virtual void run() = 0;
	virtual ~Player() {}
};

}

#endif // PLAYER_H
