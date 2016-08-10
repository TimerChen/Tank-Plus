#ifndef SPRITE_SANDBOX_H
#define SPRITE_SANDBOX_H

#include "Sprite_Base.h"
#include "SandBox.h"
namespace TankPlus
{
class Sprite_SandBox: public Sprite_Base
{
public:

	short DISPLAY;
	int x, y, z;
	Color Color_Ball_Edge, Color_Ball_Inside,Color_Wall_Edge, Color_Wall_Inside;
	Sprite_SandBox( int X = 0, int Y = 0, int Z = 0, SandBox* AIM = NULL, short dis = 0);
	SandBox *aim;
	void Draw();

};
}

#endif // SPRITE_SANDBOX_H
