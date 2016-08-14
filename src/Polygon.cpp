#include "Polygon.h"
namespace GAME
{
Polygon::Polygon()
{ IS_RECT = 0; }

Polygon::Polygon( std::vector<Point> POINTS ):
points(POINTS){ IS_RECT = 0; }

Polygon::Polygon( const Point &P1, const Point &P2 )
{
	Point p1 = P1, p2 = P2;
	if(p1.x > p2.x)std::swap(p1.x, p2.x);
	if(p1.y > p2.y)std::swap(p1.y, p2.y);

	IS_RECT = 1;

    points.push_back(p1);
    points.push_back(Point( p2.x, p1.y ));
	points.push_back(p2);
	points.push_back(Point( p1.x, p2.y ));

}

void Polygon::Move( Point v )
{

    for( int i = 0; i < points.size(); i++ )
		points[i] = points[i] + v;

}

void Polygon::MoveTo( Point p )
{
    Move( p-points[0] );
}


bool Polygon::is_rect() const
{ return IS_RECT; }

Polygon operator + ( const Polygon &a, const Point &b )
{
    Polygon re = a;
    for(int i=0; i<re.points.size(); i++)
        re.points[i] = re.points[i] + b;
    return re;
}
Polygon operator - ( const Polygon &a, const Point &b )
{
    Polygon re = a;
    for(int i=0; i<re.points.size(); i++)
        re.points[i] = re.points[i] - b;
    return re;
}
}
