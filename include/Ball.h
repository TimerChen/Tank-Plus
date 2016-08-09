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
	int id;

	Ball( int ID = 0, double M = 1, Point V = 0, double MAXV = 8 );

	//state
	Point v,cent,pos;
	double m,MAXv;
	//void InitCenter ( Point add=Point() );
	void AddV( const Point &V );
};

#endif // BALL_H
