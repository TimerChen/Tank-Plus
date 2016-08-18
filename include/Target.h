#ifndef TARGET_H
#define TARGET_H

#include "Body.h"

namespace GAME
{
class Target
{
public:
	int owner;
	int blood, maxblood;
	int shape;
	int type;//0:ball 1:wall
	void damage(int dmg);
	void enrich(int erc);
};
}

#endif // TARGET_H
