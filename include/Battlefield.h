#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "SandBox.h"
#include "Tmap.h"
#include "Player.h"
#include <vector>

namespace GAME
{
class Battlefield
{
public:
	std::vector<Player*> player;
	SandBox sandbox;

	Battlefield(const Tmap &tmap, const std::vector<Player*> &player);
	bool Run();
};
}

#endif // BATTLEFIELD_H
