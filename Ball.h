#ifndef BALL_H
#define BALL_H

#include "Body.h"
#include "Polygon.h"
#include "Color.h"

class Ball: public Body
{
public:

	Color Color_Edge,Color_Inside;
	short Default_EdgeColor,Default_InsideColor;

	Ball( Polygon SHAPE = Polygon(), double M = 1, Point V = 0, double MAXV = 8 );
	//shape
	Polygon shape;
	//state
	Point v;
	double m,MAXv;
	void Addv( const Point &V);
};

#endif // BALL_H
