/************************
    绘制多边形的精灵
************************/

#ifndef SPRITE_POLYGON_H
#define SPRITE_POLYGON_H

#include "Sprite_Base.h"
#include "Polygon.h"
namespace GAME
{
class Sprite_Polygon: public Sprite_Base
{

public:

    //static const std::string CLASS_NAME;

    short DISPLAY;
    Color Color_Edge, Color_Inside;

    Polygon poly;

    Sprite_Polygon( int X=0, int Y=0, int Z=0, Polygon POLY = Polygon(), short dis = 0 );

    //int x, y, z;

    void Draw();
};
//const std::string Sprite_Polygon::CLASS_NAME = "Sprite_Polygon";
}
#endif // SPRITE_POLYGON_H
