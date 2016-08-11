/************************
    矩形
************************/

#ifndef RECT_H
#define RECT_H

#include "Fathers.h"
#include "Polygon.h"
namespace GAME
{
class Rect: public Ghost
{

public:

	//static //const std::string CLASS_NAME;

    int x0, y0, x1, y1;

    Rect(int X0 = 0, int Y0 = 0, int X1 = 0, int Y1 = 0);


	Polygon to_poly()const;

};
}

//const std::string CLASS_NAME = "Rect";
#endif // RECT_H
