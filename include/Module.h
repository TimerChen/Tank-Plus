#ifndef MODULE_H
#define MODULE_H

#include <string>
#include "Target.h"

namespace GAME
{
class Module: public Target
{
public:
	std::string name;
};
}

#endif // MODULE_H
