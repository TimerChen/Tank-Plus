#ifndef TANK_H
#define TANK_H

#include <vector>
#include <string>
#include "Buff.h"
#include "Weapon.h"
#include "Armor.h"
#include "Sensor_Tank.h"

namespace GAME
{

class Tank
{
public:
	std::string name;
	int target; // target id
	double view, oldview;
	std::vector<Buff> buff;
	std::vector<Weapon> weapon;
	std::vector<Armor> armor;
	std::vector<Sensor_Tank> sensor;
};
}
#endif // TANK_H
