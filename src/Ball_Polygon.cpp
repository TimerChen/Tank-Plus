#include "Ball_Polygon.h"

Ball_Polygon::Ball_Polygon( Polygon SHAPE, double M, Point V, double MAXV, double ROTATE_V, double ROTATE_RANGLE, Point CENTER_SHIFT ):
rotate_v(ROTATE_V), rotate_rangle(ROTATE_RUANGLE)
{
    Ball( SHAPE, M, V, MAXV );
    InitCenter( CENTER_SHIFT );
}

void InitCenter( Point shift )
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
