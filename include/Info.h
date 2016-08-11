#ifndef INFO_H
#define INFO_H

#include "Player.h"
#include "Shell.h"
#include "Barrier.h"

namespace TankPlus
{
class PlayerInfo
{
	int id, group;
	bool visible;
	Tank tank;
};

class Info
{
	std::vector<PlayerInfo> playerinfo;
	std::vector<Shell> shell;
	std::vector<Barrier> barrier;
};
}

#endif // INFO_H
