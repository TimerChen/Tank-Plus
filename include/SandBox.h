#ifndef SANDBOX_H
#define SANDBOX_H

#include "Fathers.h"
#include "Point.h"
#include "Ball_Polygon.h"
#include "Wall.h"
#include "IndexManager.h"
#include "Hash.h"

namespace GAME
{
class SandBox: public Ghost
{
public:
	std::vector<Ball_Polygon>balls;
	std::vector<Wall>walls;
	std::vector<Point>forces;
    //std::vector< vector<short> >type_collision_bw;
    //std::vector< vector<short> >type_collision_bb;
    Point Field_Force;

	SandBox();

    int num_balls,num_walls;
    void Refresh();
    double GetNextTime();
    bool Run( double t, void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) );
    void AddForce( Point f, int id, int life = 1 );
    int AddBall( Ball_Polygon ball );
    int AddWall( Wall wall );
    bool DeleteBall( int id );
    bool DeleteWall( int id );
    static void DefaultDealBW(SandBox *box, int a, int b, Point dir);
    static void DefaultDealBB(SandBox *box, int a, int b, Point dir);

private:

    double left_time;
    IndexManager balls_im,walls_im;

    std::vector<Ball_Polygon> GetNextBalls( double t );
    bool isCollision( int a, int b, Polygon pa, Polygon pb, void Deal(SandBox *box,int a,int b,Point dir) );
    HashCode CollisionCheck( std::vector<Ball_Polygon> *b );
    void DealWithCollision( void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) );
    std::queue< std::tuple<Point, int, int> > queue_forces;

};
}
#endif // SANDBOX_H
