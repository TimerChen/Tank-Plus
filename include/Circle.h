#ifndef CIRCLE_H
#define CIRCLE_H

#include "Geometry.h"
#include "Point.h"
#include "DrawTool.h"
#include "Polygon.h"

class Circle: public Geometry
{

public:

	//static //const std::string CLASS_NAME;

	double r;
    Point o;

	Circle( double R=0, Point O=Point() );

	Polygon to_poly( int EdgeNum, double Start = 0 )const;

};

//const std::string Circle::CLASS_NAME = "Circle";

#endif // CIRCLE_H
