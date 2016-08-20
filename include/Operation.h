#ifndef OPERATION_H
#define OPERATION_H

#include "Point.h"

namespace GAME
{
class Operation
{
public:
	Point dir; //0<=len(dir)<=1
	bool shoot;
	int item, weapon; //-1
	Point gundir;

	Operation();
};
}

#endif // OPERATION_H
