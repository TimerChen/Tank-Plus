#include "Wall.h"
namespace GAME
{
Wall::Wall( Polygon SHAPE, int TYPE):
shape(SHAPE), type(TYPE)
{

	Default_EdgeColor = Default_InsideColor = 1;

}
}
