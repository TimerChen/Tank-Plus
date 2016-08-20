#include "Target.h"
#include <algorithm>

namespace GAME
{
void Target::damage(int dmg)
{
    blood = std::max(0, blood - dmg);
}
void Target::enrich(int erc)
{
    blood = std::min(maxblood, blood + erc);
}
}
