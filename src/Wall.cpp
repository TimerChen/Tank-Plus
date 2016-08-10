#include "Wall.h"
namespace TankPlus
{
Wall::Wall( Polygon SHAPE, int TYPE):
shape(SHAPE), type(TYPE)
{

	Default_EdgeColor = Default_InsideColor = 1;

}
}
