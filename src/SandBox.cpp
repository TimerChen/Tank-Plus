#include "SandBox.h"
#include "Geo_Calc.h"
#include <Ball_Polygon.h>
namespace GAME
{
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
    int fn = queue_forces.size();
    std::tuple<Point, int, int> tf;

    for( int i=0; i<num_balls; i++ )
        forces[i] = Point();
    for( int i=0; i<fn; i++ )
    {
        int id;
        tf = queue_forces.front();
        queue_forces.pop();
        id = std::get<1>(tf);
        std::get<2>(tf) = std::get<2>(tf) - 1;
        forces[id] = forces[id] + std::get<0>(tf);
        forces[id] = forces[id] + Field_Force;
        if( std::get<2>(tf)>0 ) queue_forces.push(tf);
    }

}
double SandBox::GetNextTime()
{
    //if at time l there is some collision

    //
    double l,r;
    HashCode status1,status2;
    std::vector<Ball_Polygon> tmp_balls;

    l = 0;r = left_time;

    tmp_balls = GetNextBalls(l);
    status1 = CollisionCheck( &tmp_balls );

    //想做得更精细可以暴力从中间挑几个时间check一下

    tmp_balls = GetNextBalls(r);
    status2 = CollisionCheck( &tmp_balls );

    if(status1 == status2) return r;

    while( r-l < 1e-10 )
    {
        double mid = (l + r)/2;
        tmp_balls = GetNextBalls(mid);
        status2 = CollisionCheck( &tmp_balls );
        if( status1 == status2 )
            l = mid;
        else
            r = mid;
    }
    return r;
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
    queue_forces.push(std::tuple<Point, int, int>(f,id,life));
}
int SandBox::AddBall( Ball_Polygon ball )
{
    int id;
    id = balls_im.GetNew();
    if(id >= balls.size())
    {
        balls.push_back(ball);
    }
    else
    {
        balls[id] = ball;
    }

    return id;
}
int SandBox::AddWall( Wall wall )
{
    int id;
    id = walls_im.GetNew();
    if(id >= walls.size())
    {
        walls.push_back(wall);
    }
    else
        walls[id] = wall;

    return id;
}
bool SandBox::DeleteBall( int id )
{
    if (balls_im.isAvailable(id)) return 0;
    balls_im.erase(id);
    while( balls.size() && !balls_im.isAvailable(balls.size()-1) )
    {
        balls.pop_back();
    }
    //clear old forces.
    int qn = queue_forces.size();
    for(int i=1;i<=qn;i++)
    {
        std::tuple<Point, int, int> tmpf;
        tmpf = queue_forces.front();
        queue_forces.pop();
        if(std::get<1>(tmpf) != id)queue_forces.push(tmpf);
    }
    return 1;
}
bool SandBox::DeleteWall( int id )
{
    if(walls_im.isAvailable(id)) return 0;
    walls_im.erase(id);
    while( walls.size() && !walls_im.isAvailable(walls.size()-1) )
    {
        walls.pop_back();
    }
    return 1;
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
HashCode SandBox::CollisionCheck( std::vector<Ball_Polygon> *b )
{
    std::vector<int> blist,wlist;
    balls_im.Get_index();
    walls_im.Get_index();
    blist = balls_im.index;
    wlist = walls_im.index;
    HashCode hc;
    int i,j;
    //Check Balls and Walls
    for(int ii=0; ii<blist.size(); ii++)
    for(int jj=0; jj<wlist.size(); jj++)
    {
        i = blist[ii];
        j = wlist[jj];
        if( Geo_Calc::CheckKick_PolygonToPolygon( (*b)[i].real_shape, walls[j].shape ) )
            hc = hc + ( std::to_string(i) + std::to_string(j) );
    }
    hc = hc + std::string("#");
    //Check Balls and Balls
    for(int ii=0; ii<blist.size(); ii++)
    for(int jj=0; jj<blist.size(); jj++)
    {
        i = blist[ii];
        j = wlist[jj];
        if( Geo_Calc::CheckKick_PolygonToPolygon( (*b)[i].real_shape, (*b)[j].real_shape, 1 ) )
            hc = hc + ( std::to_string(i) + std::to_string(j) );
    }

    return hc;
}
bool SandBox::isCollision( int a, int b, Polygon pa, Polygon pb, void Deal(SandBox *box, int a,int b,Point dir) )
{
    int i,j;
    for(i=0;i<pa.points.size();i++)
    for(j=0;j<pb.points.size();j++)
    if(Geo_Calc::Dis_PointToLine(pa.points[i],Line(pb.points[j],pb.points[(j+1)%pb.points.size()])) < eps)
    {
        Deal(this, a,b, pb.points[j] - pb.points[(j+1)%pb.points.size()] );
        return 1;
    }

    return 0;
}
void SandBox::DealWithCollision( void DealBW(SandBox *box, int a,int b, Point dir), void DealBB(SandBox *box, int a,int b, Point dir) )
{
    std::vector<int> blist,wlist;
    balls_im.Get_index();
    walls_im.Get_index();
    blist = balls_im.index;
    wlist = walls_im.index;
    int i,j;
    //Check Balls and Walls
    for(int ii=0; ii<balls.size(); ii++)
    {
        //balls[i].real_shape = balls[i].real_shape + balls[i].v*1e-7;
        for(int jj=0; jj<walls.size(); jj++)
        {
            i = blist[ii];
            j = wlist[jj];
            isCollision(ii, jj, balls[ii].real_shape, walls[jj].shape, SandBox::DefaultDealBW);
        }
        //balls[i].real_shape = balls[i].real_shape - balls[i].v*1e-7;
    }

    //Check Balls and Balls
    for(int ii=0; ii<balls.size(); ii++)
    {
        //balls[i].real_shape = balls[i].real_shape + balls[i].v*1e-7;
        for(int jj=0; jj<balls.size(); jj++)
        {
            //balls[j].real_shape = balls[j].real_shape + balls[j].v*1e-7;
            i = blist[ii];
            j = blist[jj];
            if (! isCollision(i, j, balls[i].real_shape, balls[j].real_shape, SandBox::DefaultDealBB) )
            isCollision(j, i, balls[j].real_shape, balls[i].real_shape, SandBox::DefaultDealBB);

            //balls[j].real_shape = balls[j].real_shape - balls[j].v*1e-7;
        }
        //balls[i].real_shape = balls[i].real_shape - balls[i].v*1e-7;
    }
}
}
