#ifndef INFO_H
#define INFO_H

#include "Player.h"
#include "Shell.h"
#include "Barrier.h"
#include "Ball_Polygon.h"

namespace GAME
{
class PlayerInfo
{
public:
	int id, group;
	bool visible;
	Tank tank;
};

class Info
{
public:
	std::vector<PlayerInfo> playerinfo;
	std::vector<Shell> *shell;
	std::vector<Target> *target;
	std::vector<Ball_Polygon> *shape;
	Barrier *barrier;
	int winner;
	bool quit;
};
}

#endif // INFO_H
