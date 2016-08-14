#ifndef OPERATION_H
#define OPERATION_H

#include "Point.h"

namespace GAME
{
class Operation
{
private:
	Point dir;
	bool shoot;
	int item, weapon; //-1
	Point gundir;
public:
	Operation();
};
}

#endif // OPERATION_H
