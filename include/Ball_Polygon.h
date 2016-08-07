#ifndef BALL_POLYGON_H
#define BALL_POLYGON_H

#include <Ball.h>


class Ball_Polygon : public Ball
{
    public:
        Polygon shape, real_shape;
        double rotate_v,rotate_rangle;

        Ball_Polygon( Polygon SHAPE = Polygon(), double M = 1, Point V = 0, double MAXV = 8,
                      double ROTATE_RANGLE = 0, Point SHIFT = Point() );
        void InitCenter( Point shift = Point() );
        void GetRealShape();

    protected:

    private:
};

#endif // BALL_POLYGON_H
