#ifndef SHELL_H
#define SHELL_H

#include "Point.h"
#include <vector>
#include "Sensor_Shell.h"

namespace GAME
{
class Shell
{
public:
	int shape, target;//id
	int attack;
	std::vector<Sensor_Shell> sensor;
};
}

#endif // SHELL_H
