#include "Ball.h"
namespace GAME
{
Ball::Ball( short TYPE_SHAPE, double M, Point V, double MAXV ):
type_shape(TYPE_SHAPE), m(M), v(V), MAXv(MAXV)
{
	Default_EdgeColor = Default_InsideColor = 1;
}


void Ball::AddV( const Point &V )
{

    v = v+V;
    //if(fabs(v.x) <= 0.2)v.x = 0;
    //if(fabs(v.y) <= 0.2)v.y = 0;
    double len = std::min( MAXv,Geo_Calc::Length(v) );
    if(len < GAME::eps)return;
    //v = Geo_Calc::Zero(v)*len;

}
}
