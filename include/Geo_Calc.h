#ifndef Geo_Calc_H
#define Geo_Calc_H

#include "Polygon.h"
#include "Point.h"
#include "Circle.h"
#include "Rect.h"
#include "Line.h"
namespace TankPlus
{
class Geo_Calc: public Ghost
{
public:

	//static //const std::string CLASS_NAME;
	//Points
    static Point Rotate( const Point &a, double rad );
    static Point Normal( const Point &a );
    static Point Zero( const Point &a );

	static double Cross( const Point &a, const Point &b);
	static double Dot( const Point &a, const Point &b);
	static double Length( const Point &a );

    //Circle
    static Point GetPoint_OnCircle( const Circle &a, double rad );
    static Circle Rotate( const Point &o, const Circle &a,double rad );
	//Polygon

	static Polygon RectToPolygon( const Rect &r );
    static Polygon CircleToPolygon( const Circle &o, int EdgeNum, double Start );
    static Polygon Rotate( const Point &o, const Polygon &a, double rad );

	//Line
	static Point GetPoint_LineToLine( const Line &a, const Line &b );
	//
	static double Dis_PointToLine( const Point &a, const Line &b, short type = 1 );
	//static double Dis_PointToPolygon
	static double Dis_LineToLine ( const Line &a, const Line &b );
    //Kick
    static bool CheckKick_LineToLine( const Line &a, const Line &b);
    static bool CheckKick_PolygonToPolygon( const Polygon &a, const Polygon &b);

};

//const std::string Geo_Calc::CLASS_NAME = "Geo_Calc";
}
#endif // Geo_Calc_H
