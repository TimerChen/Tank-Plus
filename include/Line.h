#ifndef LINE_H
#define LINE_H

#include "Geometry.h"
#include "Point.h"
namespace GAME
{
class Line: public Geometry
{
public:
	Point p, v;
	Line( const Point &p1 = Point(), const Point &p2 = Point() );

};
}
#endif // LINE_H
