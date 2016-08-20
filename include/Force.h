#ifndef FORCE_H
#define FORCE_H

#include <Point.h>

namespace GAME
{


class Force
{
    public:
        Force(Point V, int AIM, int LIFE = 1);
        Point v;
        int aim, life;
};

}
#endif // FORCE_H
