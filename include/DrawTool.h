#ifndef DRAWTOOL_H
#define DRAWTOOL_H

#include "Fathers.h"
#include "Color.h"
namespace TankPlus
{
class DrawTool: public Ghost
{
public:

    //static //const std::string CLASS_NAME;

    static double Getx(int X);
    static double Gety(int Y);
    static double Getz(int Z);
    static void DrawPoint3(int X, int Y, int Z);
	static void SetColor(Color c);
};
//const std::string DrawTool::CLASS_NAME = "DrawTool";
}

#endif // DRAWTOOL_H
