#ifndef WALL_H
#define WALL_H

#include "Body.h"
#include "Polygon.h"
#include "Color.h"
namespace GAME
{
class Wall: public Body
{
public:
	Polygon shape;
	Color Color_Edge,Color_Inside;
	short Default_EdgeColor,Default_InsideColor;
	short type_shape;
    Wall( short TYPE_SHAPE = 1, Polygon SHAPE = Polygon() );

};
}
#endif // WALL_H
