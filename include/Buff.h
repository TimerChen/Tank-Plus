#ifndef BUFF_H
#define BUFF_H

#include <string>

namespace GAME
{
class Tank;

class Buff
{
public:
	int life;
	std::string name;

	virtual bool effect(Tank &target) = 0;
	// return false if there is no life left

	int live();
};
}

#endif // BUFF_H
