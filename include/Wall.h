#ifndef WALL_H
#define WALL_H

#include "Body.h"
#include "Polygon.h"
#include "Color.h"
namespace TankPlus
{
class Wall: public Body
{
public:
	Polygon shape;
	Color Color_Edge,Color_Inside;
	short Default_EdgeColor,Default_InsideColor;
    Wall( Polygon SHAPE = Polygon(), int TYPE = 0 );
	int type;

};
}
#endif // WALL_H
