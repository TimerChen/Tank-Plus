#ifndef Geo_Calc_H
#define Geo_Calc_H

#include "Polygon.h"
#include "Point.h"
#include "Circle.h"
#include "Rect.h"
#include "Line.h"
namespace GAME
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
	static bool PointInPolygon( const Point &a, const Polygon &b );
	static Polygon RectToPolygon( const Rect &r );
    static Polygon CircleToPolygon( const Circle &o, int EdgeNum, double Start );
    static Polygon Rotate( const Point &o, const Polygon &a, double rad );
    static double GetPolygonArea( const Polygon &a );
    static double GetPolygonArea( const Polygon &a, const Point &b );
    static Point GetPolygonCenter( const Polygon &a );
	//Line
	static Point GetPoint_LineToLine( const Line &a, const Line &b );
	//
	//0:直线 1:线段
	static double Dis_PointToLine( const Point &a, const Line &b, short type = 1 );
	//0:多边形只有边框 1:实心多边形
	static double Dis_PointToPolygon( const Point &a, const Polygon &b, short type = 1 );
	static double Dis_LineToLine ( const Line &a, const Line &b );
    //Kick
    static bool CheckKick_LineToLine( const Line &a, const Line &b);
    static bool CheckKick_PolygonToPolygon( const Polygon &a, const Polygon &b,short type = 1 );
    //Visible
    static bool CheckVisible(const Point &p1, const Point &p2, const Polygon &poly);

};

//const std::string Geo_Calc::CLASS_NAME = "Geo_Calc";
}
#endif // Geo_Calc_H
