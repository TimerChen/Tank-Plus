/************************
    绘制多边形的精灵
************************/

#ifndef SPRITE_CIRCLE_H
#define SPRITE_CIRCLE_H

#include "Sprite_Base.h"
#include "Circle.h"
#include "Color.h"

namespace TankPlus
{
class Sprite_Circle: public Sprite_Base
{

public:

    //static const std::string CLASS_NAME;
    static const int MAX_POINT;
    static const double MIN_LENGTH;

    short DISPLAY;
    Color Color_Edge, Color_Inside;

    Circle cir;

    Sprite_Circle( int X=0, int Y=0, int Z=0, Circle CIR = Circle(), short dis = 0 );

    //int x, y, z;

    void Draw();

};
//const std::string Sprite_Circle::CLASS_NAME = "Sprite_Circle";
}
#endif // SPRITE_CIRCLE_H
