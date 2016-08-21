#ifndef SANDBOX_H
#define SANDBOX_H

#include "Fathers.h"
#include "Point.h"
#include "Ball_Polygon.h"
#include "Wall.h"
#include "IMvector.h"
#include "Hash.h"
#include "Force.h"

namespace GAME
{
class SandBox: public Ghost
{
public:
	IMvector<Ball_Polygon>balls;
	IMvector<Wall>walls;
	IMvector<Point>forces;
    //std::vector< vector<short> >type_collision_bw;
    //std::vector< vector<short> >type_collision_bb;
    Point Field_Force;

	SandBox();

    //int num_balls,num_walls;
    void Refresh( short first=1 );
    double GetNextTime();
    bool Run( double t, void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) );
    int AddForce( Force f );
    int AddBall( Ball_Polygon ball );
    int AddWall( Wall wall );
    bool DeleteForces( int id );
    bool DeleteBall( int id );
    bool DeleteWall( int id );
    void AddTracing( int id, int aim, short type=1 );
    void ClearTracing( int id );
    static void DefaultDealBW(SandBox *box, int a, int b, Point dir);
    static void DefaultDealBB(SandBox *box, int a, int b, Point dir);

    IMvector<int>tracing;
private:

    double left_time;

    //IndexManager balls_im,walls_im;

    IMvector<Ball_Polygon> GetNextBalls( double t );
    bool isCollision( int a, int b, Polygon pa, Polygon pb, void Deal(SandBox *box,int a,int b,Point dir) );
    HashCode CollisionCheck( IMvector<Ball_Polygon> *b );
    void DealWithCollision( void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) );
    IMvector<Force>raw_forces;

};
}
#endif // SANDBOX_H
