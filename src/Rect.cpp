#include "Rect.h"
namespace TankPlus
{
Rect::Rect(int X0, int Y0, int X1, int Y1 )
:x0(X0), y0(Y0), x1(X1), y1(Y1){}

Polygon Rect::to_poly() const
{ return Polygon( Point(x0, y0), Point(x1, y1)); }
}
