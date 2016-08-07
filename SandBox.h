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
	int KickWalls( Ball b );
	bool KickTmpBalls( Ball b, int ignore = -1 );
	void Update( double time = 1 );
	bool GetNextBall( double time = 1 );
	void GoNext();
	void GetKick( double use = 0, short type = 0 );
	int CantMove( int i );
    void AddForce( Point F, int aim = 0, int life = 1 );

private:
	std::queue< std::tuple<Point, int, double> > wait_f;
	std::vector<Ball>TmpB;
	std::vector<Point>TmpF;
};

#endif // SANDBOX_H
