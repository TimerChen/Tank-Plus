#ifndef WEAPON_H
#define WEAPON_H

#include "Module.h"

namespace TankPlus
{
class Battlefield;
class Point;

class Weapon: public Module
{
public:
	int attack, oldattack, failatk;
	double penetrate, oldpenetrate;
	void shoot(Battlefield *field, const Point &pos);
};
}

#endif // WEAPON_H
