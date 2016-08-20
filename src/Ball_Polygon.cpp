#include "Ball_Polygon.h"
#include <Geo_Calc.h>
namespace GAME
{
Ball_Polygon::Ball_Polygon( short TYPE_SHAPE, double M, Point V, double MAXV, Polygon SHAPE, double ROTATE_V, double ROTATE_RANGLE, Point CENTER_SHIFT ):
Ball( TYPE_SHAPE, M, V, MAXV ), shape(SHAPE), rotate_v( ROTATE_V ), rotate_rangle( ROTATE_RANGLE )
{
    InitCenter( CENTER_SHIFT );
    I = m * Geo_Calc::CalcInertia(shape);
}

void Ball_Polygon::AddRotateV( double ROTATE_V )
{

    rotate_v += ROTATE_V;

}

void Ball_Polygon::InitCenter( Point shift )
{
    /*cent = Point();
    for(int i=0; i<shape.points.size(); i++)
        cent = cent + shape.points[i];
    cent = cent / shape.points.size();*/
    cent = Geo_Calc::GetPolygonCenter(shape);
    cent = cent + shift;
}

void Ball_Polygon::GetRealShape()
{

    Point tmpv;
    real_shape = shape;
    real_shape = Geo_Calc::Rotate(cent,real_shape,rotate_rangle);
    real_shape.Move(pos);

}
}
