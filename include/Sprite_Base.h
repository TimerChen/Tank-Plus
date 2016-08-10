/************************
    精灵的基类
************************/

#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

#include <GL/gl.h>
#include "Fathers.h"
#include "DrawTool.h"
namespace TankPlus
{
class Sprite_Base: public Entity
{
public:
    //static //const std::string CLASS_NAME;

	short DISPLAY;

    Sprite_Base( int X = 0, int Y = 0, int Z = 0 ):
    Entity(), x(X), y(Y), z(Z) {}

    int x, y, z;

    void Draw();
};

//static //const std::string CLASS_NAME = "Sprite_Base";
}
#endif
