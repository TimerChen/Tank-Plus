#include "Geo_Calc.h"
namespace GAME
{
Point Geo_Calc::Rotate( const Point &a, double rad )
{ return Point( a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad) ); }

Point Geo_Calc::Normal( const Point &a )
{ return Point( -a.y, a.x ); }

Point Geo_Calc::Zero( const Point &a )
{ return a/Length(a); }

double Geo_Calc::Cross( const Point &a, const Point &b)
{ return a.x*b.y - a.y*b.x; }

double Geo_Calc::Dot( const Point &a, const Point &b )
{ return a.x*b.x + a.y*b.y; }

double Geo_Calc::Length( const Point &a )
{ return sqrt( Dot( a, a ) ); }

Point Geo_Calc::GetPoint_OnCircle( const Circle &a, double rad )
{

    Point v = Rotate( Point(0, a.r), rad );
    return a.o + v;

}

Circle Geo_Calc::Rotate( const Point &o, const Circle &a, double Rad )
{

    Point v = a.o - o;
	v = Rotate( v, Rad );
	return Circle( a.r, o+v );

}


Polygon Geo_Calc::RectToPolygon( const Rect &r )
{

	return r.to_poly();

}
Polygon Geo_Calc::CircleToPolygon( const Circle &o, int EdgeNum, double Start )
{

    return o.to_poly( EdgeNum, Start );

}

Polygon Geo_Calc::Rotate( const Point &o, const Polygon &a, double Rad )
{
	Polygon re;
	Point v;

	for( int i = 0; i < a.points.size(); i++ )
	{
		v = a.points[i] - o;
        v = Rotate( v, Rad );
        re.points.push_back( o+v );
	}

	return re;
}

Point Geo_Calc::GetPoint_LineToLine( const Line &a, const Line &b)
{

    Point u = a.p - b.p;
	double t = Cross( b.v, u ) / Cross( a.v, b.v );
	return a.p + a.v*t;

}

double Geo_Calc::Dis_PointToLine( const Point &a, const Line &b, short type )
{
    if(!type) return fabs( Cross( b.v, a-b.p ) / Length( b.v ) );
	Point v1 = b.v, v2 = a - b.p, v3 = a - (b.p+b.v);
	if( Dot( v1, v2 ) < -eps )return Length(v2);
	else if( Dot( v1, v3 ) > eps ) return Length(v3);
	return fabs( Cross( b.v, a-b.p ) / Length( b.v ) );

}
double Geo_Calc::Dis_LineToLine ( const Line &a, const Line &b )
{
	if( CheckKick_LineToLine(a,b) )return 0;

    double re = 1e50;
    re = std::min( re, Dis_PointToLine( a.p, b ) );
    re = std::min( re, Dis_PointToLine( a.p+a.v, b ) );
    re = std::min( re, Dis_PointToLine( b.p, a ) );
    re = std::min( re, Dis_PointToLine( b.p+b.v, a ) );

	return re;

}
//kick
bool Geo_Calc::CheckKick_LineToLine( const Line &a, const Line &b )
{
	double ba = Cross( a.p - b.p, b.v )*Cross( a.p+a.v - b.p, b.v ),
			bb = Cross( b.p - a.p, a.v )*Cross( b.p+b.v - a.p, a.v );

    return ba < -eps && bb < -eps;

}
bool Geo_Calc::CheckKick_PolygonToPolygon( const Polygon &a, const Polygon &b )
{
	int i, j;

	for( i = 0; i < a.points.size(); i++ )
	for( j = 0; j < b.points.size(); j++ ){

		if(Dis_LineToLine( 	Line(a.points[i],a.points[(i+1)%a.points.size()]),
									Line(b.points[j],b.points[(j+1)%b.points.size()]) ) < eps*3 ){
			return 1;
		}
	}
	return 0;
}
}
