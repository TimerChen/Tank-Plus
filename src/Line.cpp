#include "Line.h"
namespace TankPlus
{
Line::Line( const Point &p1, const Point &p2 ):
p(p1), v(p2-p1){ }
}
