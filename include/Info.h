#ifndef INFO_H
#define INFO_H

#include "Player.h"
#include "Shell.h"
#include "SandBox.h"
#include "Target.h"
#include "IMvector.h"
#include <map>
#include <string>

namespace GAME
{
class PlayerInfo
{
public:
	int id, group;
	std::string name;
	Tank *tank;
};

class Info
{
public:
	std::vector<PlayerInfo> playerinfo;
	IMvector<Shell> *shell;
	IMvector<Target> *target;
	std::map<int, int> *barrier;
	IMvector<Ball_Polygon> *ball;
	IMvector<Wall> *wall;
	int winner;
	bool quit;
private:
};
}

#endif // INFO_H
