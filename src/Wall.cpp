#include "Wall.h"
namespace GAME
{

Wall::Wall( short TYPE_SHAPE, Polygon SHAPE ):
type_shape(TYPE_SHAPE), shape(SHAPE)
{

	Default_EdgeColor = Default_InsideColor = 1;

}

}
