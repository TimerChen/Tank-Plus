#include "Line.h"
namespace GAME
{
Line::Line( const Point &p1, const Point &p2 ):
p(p1), v(p2-p1){ }
}
