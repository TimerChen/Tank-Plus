#include "Operation.h"

namespace GAME
{

Operation::Operation()
    : dir(0, 0), gundir(1, 0)
{
    shoot = false;
    item = -1;
    weapon = 0;
}

}
