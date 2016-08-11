#include "Ball_Polygon.h"
#include <Geo_Calc.h>
namespace GAME
{
Ball_Polygon::Ball_Polygon( int ID, double M, Point V, double MAXV, Polygon SHAPE, double ROTATE_V, double ROTATE_RANGLE, Point CENTER_SHIFT ):
Ball( ID, M, V, MAXV ), shape(SHAPE), rotate_v( ROTATE_V ), rotate_rangle( ROTATE_RANGLE )
{
    InitCenter( CENTER_SHIFT );
}

void Ball_Polygon::AddRotateV( double ROTATE_V )
{

    rotate_v += ROTATE_V;

}

void Ball_Polygon::InitCenter( Point shift )
{
    cent = Point();
    for(int i=0; i<=shape.points.size(); i++)
        cent = cent + shape.points[i];
    cent = cent / shape.points.size();
    cent = cent + shift;
}

void Ball_Polygon::GetRealShape()
{

    Point tmpv;
    real_shape = shape;
    for(int i=0; i<shape.points.size(); i++)
    {
        tmpv = shape.points[i] - cent;
        tmpv = Geo_Calc::Rotate( tmpv, rotate_rangle );
        real_shape.points[i] = cent + tmpv + pos;
    }

}
}
