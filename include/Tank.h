#ifndef TANK_H
#define TANK_H

#include <vector>
#include <string>
#include "Weapon.h"
#include "Armor.h"
#include "Buff.h"
#include "Sensor_Tank.h"
#include "Target.h"

namespace GAME
{
class Tank
{
public:
	std::string name;
	int id; // tank id
	int target; // target id
	double view, oldview;
	std::vector<Buff> buff;
	std::vector<Weapon> weapon;
	std::vector<Armor> armor;
	std::vector<Sensor_Tank> sensor;
};
}
#endif // TANK_H
