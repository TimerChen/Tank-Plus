/************************
    几何中点的类
************************/

#ifndef POINT_H
#define POINT_H

#include "Geometry.h"
namespace TankPlus
{
class Point: public Geometry
{

public:

	//static //const std::string CLASS_NAME;

	Point(double X = 0, double Y = 0)
	:x(X),y(Y){}

	double x,y;

};

//const std::string Point::CLASS_NAME = "Point";

Point operator + ( const Point &a ,const Point &b );

Point operator - ( const Point &a ,const Point &b );

Point operator * ( const Point &a ,double b );

Point operator / ( const Point &a ,double b );

}

#endif // POINT_H
