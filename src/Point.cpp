#include "Point.h"
namespace GAME
{
Point operator + ( const Point &a ,const Point &b )
{ return Point(a.x + b.x, a.y + b.y); }

Point operator - ( const Point &a ,const Point &b )
{ return Point(a.x - b.x, a.y - b.y); }

Point operator * ( const Point &a ,double b )
{ return Point(a.x*b, a.y*b); }

Point operator / ( const Point &a ,double b )
{ return Point(a.x/b, a.y/b); }
}
