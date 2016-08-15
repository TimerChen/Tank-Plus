/************************
    多边形的类
************************/

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Point.h"
namespace GAME
{
class Polygon: public Geometry
{

public:

    //static //const std::string CLASS_NAME;

    std::vector<Point> points;
    Polygon();
    Polygon(std::vector<Point> POINTS);
    Polygon(const Point &p1, const Point &p2);

    void Move(Point v);
    void MoveTo(Point p);

    bool is_rect() const;

private:
    bool IS_RECT;
};

Polygon operator + (const Polygon &a, const Point &b);
Polygon operator - (const Polygon &a, const Point &b);
//const std::string Polygon::CLASS_NAME = "Polygon";

}
#endif // POLYGON_H
