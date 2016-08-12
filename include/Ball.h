#ifndef BALL_H
#define BALL_H

#include "Geo_Calc.h"
#include "Body.h"
#include "Color.h"
namespace GAME
{
class Ball: public Body
{
public:

	Color Color_Edge,Color_Inside;
	short Default_EdgeColor,Default_InsideColor;
	//0:只有边框 1:实心
	short type_shape;


	Ball( short TYPE_SHAPE = 1, double M = 1, Point V = 0, double MAXV = 8 );

	//state
	Point v,cent,pos;
	double m,MAXv;
	//void InitCenter ( Point add=Point() );
	void AddV( const Point &V );
};
}

#endif // BALL_H
