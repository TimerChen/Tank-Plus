#ifndef CIRCLE_H
#define CIRCLE_H

#include "Polygon.h"
#include "DrawTool.h"
namespace TankPlus
{
class Circle: public Geometry
{

public:

    //static //const std::string CLASS_NAME;

    double r;
    Point o;

    Circle(double R = 0, Point O = Point());

    Polygon to_poly(int EdgeNum, double Start = 0)const;

};
}
//const std::string Circle::CLASS_NAME = "Circle";

#endif // CIRCLE_H
