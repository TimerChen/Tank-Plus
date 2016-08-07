#include "Circle.h"
#include "Geo_Calc.h"

Circle::Circle( double R, Point O ):
r(R), o(O){}

Polygon Circle::to_poly( int EdgeNum, double Start ) const
{
	using namespace std;

	double Per_Rad = 2*M_PI / EdgeNum;
	vector<Point>tmp;

    for( int i = 0; i<EdgeNum; i++ ){
        tmp.push_back( Geo_Calc::GetPoint_OnCircle( *this, Start+Per_Rad*i ) );
    }

	return Polygon(tmp);

}
