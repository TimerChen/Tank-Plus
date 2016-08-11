#ifndef SHELL_H
#define SHELL_H

#include "Point.h"
#include <vector>
#include "Sensor_Shell.h"

namespace TankPlus
{
class Shell: public Target
{
public:
	int shape;//id
	Point target;
	int attack, failatk;
	double penetrate;
	std::vector<Sensor_Shell> sensor;
};
}

#endif // SHELL_H
