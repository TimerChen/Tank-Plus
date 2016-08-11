#ifndef SANDBOX_H
#define SANDBOX_H

#include "Fathers.h"
#include "Point.h"
#include "Ball_Polygon.h"
#include "Wall.h"
namespace GAME
{
class SandBox: public Ghost
{
public:
	std::vector<Ball_Polygon>balls;
	std::vector<Wall>walls;
	std::vector<Point>forces;

    Point Field_Force;

	SandBox();
	/*
	int KickWalls( Ball b );
	bool KickTmpBalls( Ball b, int ignore = -1 );
	void Update( double time = 1 );
	bool GetNextBall( double time = 1 );
	void GoNext();
	void GetKick( double use = 0, short type = 0 );
	int CantMove( int i );
    void AddForce( Point F, int aim = 0, int life = 1 );
    */
    int num_balls,num_walls;
    void Refresh();
    double GetNextTime();
    bool Run( double t, void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) );
    void AddForce( Point f, int id, int life = 1 );
    int AddBall( Ball ball );
    int AddWall( Wall wall );
    bool DeleteBall( int id );
    bool DeleteWall( int id );
    static void DefaultDealBW(SandBox *box, int a, int b, Point dir);
    static void DefaultDealBB(SandBox *box, int a, int b, Point dir);

private:

    double left_time;

    std::vector<Ball_Polygon> GetNextBalls( double t );
    bool isCollision( int a, int b, Polygon pa, Polygon pb, void Deal(SandBox *box,int a,int b,Point dir) );
    bool CollisionCheck( std::vector<Ball_Polygon> *b );
    void DealWithCollision( void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) );
    std::queue< std::tuple<Point, int, int> > forcesqueue;
    /*
	std::queue< std::tuple<Point, int, double> > wait_f;
	std::vector<Ball>TmpB;
	std::vector<Point>TmpF;
	*/
};
}
#endif // SANDBOX_H
