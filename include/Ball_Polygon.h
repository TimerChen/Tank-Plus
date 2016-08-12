#ifndef BALL_POLYGON_H
#define BALL_POLYGON_H

#include <Ball.h>

namespace GAME
{
class Ball_Polygon : public Ball
{
    public:
        Polygon shape, real_shape;
        double rotate_v,rotate_rangle;

        Ball_Polygon( short TYPE_SHAPE = 1, double M = 1, Point V = 0, double MAXV = 8, Polygon SHAPE = Polygon(),
                      double ROTATE_V = 0, double ROTATE_RANGLE = 0, Point CENTER_SHIFT = Point() );
        void InitCenter( Point shift = Point() );
        void GetRealShape();
        void AddRotateV( double ROTATE_V );

    protected:

    private:
};
}

#endif // BALL_POLYGON_H
