#include "SandBox.h"
#include "Geo_Calc.h"
#include <Ball_Polygon.h>

//Public Functions
SandBox::SandBox()
{
    num_balls = num_walls = 0;
    Field_Force = Point();
    left_time = 1;
}
void SandBox::Refresh()
{
    //Reset left time
    left_time = 1;

    //Add forces
    int fn = forcesqueue.size();
    std::tuple<Point, int, int> tf;

    for( int i=0; i<num_balls; i++ )
        forces[i] = Point();
    for( int i=0; i<fn; i++ )
    {
        int id;
        tf = forcesqueue.front();
        forcesqueue.pop();
        id = std::get<1>(tf);
        std::get<2>(tf) = std::get<2>(tf) - 1;
        forces[id] = forces[id] + std::get<0>(tf);
        forces[id] = forces[id] + Field_Force;
        if( std::get<2>(tf)>0 ) forcesqueue.push(tf);
    }

}
double SandBox::GetNextTime()
{
    //if at time l there is some collision

    //
    double l,r;
    std::vector<Ball_Polygon> tmp_balls;
    l = 0;r = left_time;
    while( r-l < 1e-10 )
    {
        double mid = (l + r)/2;
        tmp_balls = GetNextBalls(mid);
        if( CollisionCheck( &tmp_balls ) )
            r = mid;
        else
            l = mid;
    }
    return l;
}
bool SandBox::Run(double t, void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) )
{
    if(left_time <= 0)return 0;
    balls = GetNextBalls(t);
    //...
    DealWithCollision( DealBW, DealBB );
    return 1;
}
void SandBox::AddForce( Point f, int id, int life )
{
    if(id >= balls.size())return; //Error occurred.
    forcesqueue.push(std::tuple<Point, int, int>(f,id,life));
}
void SandBox::DefaultDealBW( SandBox *box, int a, int b, Point dir )
{

    dir = dir / sqrt(Geo_Calc::Dot(dir,dir));

    box->balls[a].rotate_v = 0;
    Point tv;
    tv = dir * Geo_Calc::Dot( box->balls[a].v, dir );
    box->balls[a].v = box->balls[a].v - tv * (1 + 0.1);//ratio?
}
void SandBox::DefaultDealBB( SandBox *box, int a, int b, Point dir )
{
    dir = dir / sqrt(Geo_Calc::Dot(dir,dir));

    box->balls[a].rotate_v = 0;
    box->balls[b].rotate_v = 0;
    Point tv1, tv2;
    double v1,v2,m1,m2,v11,v22;
    m1 = box->balls[a].m;
    m2 = box->balls[b].m;
    v1 = Geo_Calc::Dot( box->balls[a].v, dir );
    v2 = Geo_Calc::Dot( box->balls[b].v, dir );
    box->balls[a].v = box->balls[a].v - dir * v1;
    box->balls[b].v = box->balls[b].v - dir * v2;
    v11 = (v1*(m1 - m2) + 2*m2*v2)/(m1 + m2);
    v22 = (v2*(m2 - m1) + 2*m1*v1)/(m1 + m2);
    box->balls[a].v = box->balls[a].v + dir * v11 * 0.5;//ratio?
    box->balls[b].v = box->balls[b].v + dir * v22 * 0.5;//ratio?
}
//Private Functions
std::vector<Ball_Polygon> SandBox::GetNextBalls( double t )
{
    std::vector<Ball_Polygon> reballs;
    Ball_Polygon tb;
    Point tv;
    for(int i=0; i < balls.size(); i++)
    {
        tb = balls[i];
        tb.AddV( forces[i] / tb.m );
        tb.pos = tb.pos + tb.v * t;
        tb.rotate_rangle += tb.rotate_v * t;
        tb.GetRealShape();
        reballs.push_back(tb);
    }
    return reballs;
}
bool SandBox::CollisionCheck( std::vector<Ball_Polygon> *b )
{

    //Check Balls and Walls
    for(int i=0; i<(*b).size(); i++)
    for(int j=0; j<walls.size(); j++)
    if( Geo_Calc::CheckKick_PolygonToPolygon( (*b)[i].real_shape, walls[j].shape ) )
        return 1;
    //Check Balls and Balls
    for(int i=0; i<(*b).size(); i++)
    for(int j=0; j<(*b).size(); j++)
    if( Geo_Calc::CheckKick_PolygonToPolygon( (*b)[i].real_shape, (*b)[j].real_shape ) )
        return 1;
    return 0;
}
bool SandBox::isCollision( int a, int b, Polygon pa, Polygon pb, void Deal(SandBox *box, int a,int b,Point dir) )
{
    int i,j;
    for(i=0;i<pa.points.size();i++)
    for(j=0;j<pb.points.size();j++)
    if(Geo_Calc::Dis_PointToLine(pa.points[i],Line(pb.points[j],pb.points[(j+1)%pb.points.size()])) < GAME::eps)
    {
        Deal(this, a,b, pb.points[j] - pb.points[(j+1)%pb.points.size()] );
        return 1;
    }

    return 0;
}
void SandBox::DealWithCollision( void DealBW(SandBox *box, int a,int b, Point dir), void DealBB(SandBox *box, int a,int b, Point dir) )
{
    //Check Balls and Walls
    for(int i=0; i<balls.size(); i++)
    {
        balls[i].real_shape = balls[i].real_shape + balls[i].v*1e-7;
        for(int j=0; j<walls.size(); j++)
        {
            isCollision(i, j, balls[i].real_shape, walls[j].shape, SandBox::DefaultDealBW);
        }
        balls[i].real_shape = balls[i].real_shape - balls[i].v*1e-7;
    }

    //Check Balls and Balls
    for(int i=0; i<balls.size(); i++)
    {
        balls[i].real_shape = balls[i].real_shape + balls[i].v*1e-7;
        for(int j=0; j<balls.size(); j++)
        {
            balls[j].real_shape = balls[j].real_shape + balls[j].v*1e-7;

            if (! isCollision(i, j, balls[i].real_shape, balls[j].real_shape, SandBox::DefaultDealBB) )
            isCollision(j, i, balls[j].real_shape, balls[i].real_shape, SandBox::DefaultDealBB);

            balls[j].real_shape = balls[j].real_shape - balls[j].v*1e-7;
        }
        balls[i].real_shape = balls[i].real_shape - balls[i].v*1e-7;
    }
}
