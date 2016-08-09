#ifndef SANDBOX_H
#define SANDBOX_H

#include "Fathers.h"
#include "Point.h"
#include "Ball.h"
#include "Wall.h"

class SandBox: public Ghost
{
public:
	std::vector<Ball>balls;
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
    bool Run( double t, void DealBW(int a,int b,Point dir), void DealBB(int a,int b,Point dir) );
    void AddForce( Point f, int id, int life = 1 );

    static void DefaultDealBW(int a, int b, Point dir);
    static void DefaultDealBB(int a, int b, Point dir);

private:

    double left_time;

    std::vector<Ball> GetNextBalls( double t );
    bool isCollision( int a, int b, Polygon pa, Polygon pb, void Deal(int a,int b,Point dir) );
    bool CollisionCheck();
    void DealWithCollision( void DealBW(int a,int b,Point dir), void DealBB(int a,int b,Point dir) );
    std::queue< std::tuple<Point, int, int> > forcesqueue;
    /*
	std::queue< std::tuple<Point, int, double> > wait_f;
	std::vector<Ball>TmpB;
	std::vector<Point>TmpF;
	*/
};

#endif // SANDBOX_H
