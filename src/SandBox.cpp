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

    //Add Field_Force
    const std::set<int> *fset = forces.GetIndex();
    for(std::set<int>::iterator ii = fset->begin();ii!=fset->end();ii++)
    {
        int i = *ii;
        forces[i] = Field_Force;
    }
    if (RunTimes == 26)
        RunTimes = 26;
    //Add forces
    int fn = queue_forces.size();
    std::tuple<Point, int, int> tf;

    for( int i=0; i<fn; i++ )
    {
        int id;
        tf = queue_forces.front();
        queue_forces.pop();
        id = std::get<1>(tf);
        std::get<2>(tf) = std::get<2>(tf) - 1;
        forces[id] = forces[id] + std::get<0>(tf);
        if( std::get<2>(tf)>0 ) queue_forces.push(tf);
    }
    printf("fn:%d\n",fn);

}
double SandBox::GetNextTime()
{
    //if at time l there is some collision

    //
    double l,r;
    HashCode status1,status2;
    IMvector<Ball_Polygon> tmp_balls;

    l = 0;r = left_time;
    //printf("check l\n");
    tmp_balls = GetNextBalls(l);
    status1 = CollisionCheck( &tmp_balls );

    //想做得更精细可以暴力从中间挑几个时间check一下
    //printf("check r\n");
    double step = 0.01;
    short check = 0;
    for(double tt = l+step;tt<=r;tt+=step)
    {
        tmp_balls = GetNextBalls(tt);
        status2 = CollisionCheck( &tmp_balls );
        if( !(status1 == status2) )
        {
            check = 1;
            r = tt;
            break;
        }
    }
    if(!check)
    {
        tmp_balls = GetNextBalls(r);
        status2 = CollisionCheck( &tmp_balls );

        if(status1 == status2) return r;
    }
    //printf("start mid find\n");
    while( r-l > 1e-10 )
    {
        //printf("%f %f\n",l,r);
        double mid = (l + r)/2;
        tmp_balls = GetNextBalls(mid);
        status2 = CollisionCheck( &tmp_balls );
        if( status1 == status2 )
            l = mid;
        else
            r = mid;
    }
    if(l == 0)return r;
    return l;
}
bool SandBox::Run(double t, void DealBW(SandBox *box,int a,int b,Point dir), void DealBB(SandBox *box,int a,int b,Point dir) )
{
    if(left_time <= 0)return 0;
    balls = GetNextBalls(t);
    //...
    DealWithCollision( DealBW, DealBB );
    left_time -= t;
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
    id = balls.insert(ball);
    forces.insert(Point());
    return id;
}
int SandBox::AddWall( Wall wall )
{
    int id;
    id = walls.insert(wall);
    forces.insert(Point());
    return id;
}
bool SandBox::DeleteBall( int id )
{
    if(!balls.erase(id))return 0;
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
    if(!walls.erase(id)) return 0;
    return 1;
}
void SandBox::DefaultDealBW( SandBox *box, int a, int b, Point dir )
{

    dir = Geo_Calc::Zero(dir);
    dir = Geo_Calc::Normal(dir);

    //box->balls[a].rotate_v = 0;
    Point tv;
    //printf("(%f, %f)",dir.x,dir.y);
    printf("(%f, %f)\n",box->balls[a].v.x,box->balls[a].v.y);
    tv = dir * Geo_Calc::Dot( box->balls[a].v, dir );
    //printf("(%f, %f)",dir.x,dir.y);
    box->balls[a].v = box->balls[a].v - tv * (1 + 1);//ratio?
}
void SandBox::DefaultDealBB( SandBox *box, int a, int b, Point dir )
{
    dir = Geo_Calc::Zero(dir);
    dir = Geo_Calc::Normal(dir);

    //box->balls[a].rotate_v = 0;
    //box->balls[b].rotate_v = 0;
    Point tv1, tv2;
    double v1,v2,m1,m2,v11,v22;
    m1 = box->balls[a].m;
    m2 = box->balls[b].m;
    v1 = Geo_Calc::Dot( box->balls[a].v, dir );

    v2 = Geo_Calc::Dot( box->balls[b].v, dir );

    printf("%f %f\n",v1,v2);
    printf("kira");
    box->balls[a].v = box->balls[a].v - dir * v1;
    printf("%f %f\n",box->balls[a].v.x,box->balls[a].v.y);
    box->balls[b].v = box->balls[b].v - dir * v2;
    printf("%f %f\n",box->balls[b].v.x,box->balls[b].v.y);
    v11 = (v1*(m1 - m2) + 2*m2*v2)/(m1 + m2);
    v22 = (v2*(m2 - m1) + 2*m1*v1)/(m1 + m2);
    box->balls[a].v = box->balls[a].v + dir * v11 * 1;//ratio?
    printf("%f %f\n",box->balls[a].v.x,box->balls[a].v.y);
    box->balls[b].v = box->balls[b].v + dir * v22 * 1;//ratio?
    printf("%f %f\n",box->balls[b].v.x,box->balls[b].v.y);
}
//Private Functions
IMvector<Ball_Polygon> SandBox::GetNextBalls( double t )
{
    IMvector<Ball_Polygon> reballs;
    const std::set<int> *set_ball = balls.GetIndex();
    reballs = balls;
    Ball_Polygon tb;
    Point tv;
    //set_ball = balls.GetIndex();
    for(std::set<int>::iterator ii = set_ball->begin();ii!=set_ball->end();ii++)
    {
        int i = *ii;
        tb = balls[i];
        tb.AddV( forces[i] / tb.m );
        tb.pos = tb.pos + tb.v * t;
        tb.rotate_rangle += tb.rotate_v * t;
        tb.GetRealShape();
        reballs[i] = tb;
        //reballs.insert(tb);
    }
    return reballs;
}
HashCode SandBox::CollisionCheck( IMvector<Ball_Polygon> *b )
{
    const std::set<int> *bset = b->GetIndex();
    const std::set<int> *wset = walls.GetIndex();
    HashCode hc;
    int i,j;
    //Check Balls and Walls
    for(std::set<int>::iterator ii=bset->begin(); ii!=bset->end(); ii++)
    for(std::set<int>::iterator jj=wset->begin();jj!=wset->end();jj++)
    {
        i = *ii;
        j = *jj;
        if( Geo_Calc::CheckKick_PolygonToPolygon( (*b)[i].real_shape, walls[j].shape ) )
            hc = hc + ( std::to_string(i) + std::to_string(j) );
    }
    hc = hc + std::string("#");
    //Check Balls and Balls
    for(std::set<int>::iterator ii=bset->begin(); ii!=bset->end(); ii++)
    for(std::set<int>::iterator jj=ii; jj!=bset->end(); jj++)
    if(ii!=jj){
        i = *ii;
        j = *jj;
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
    {
        double dis = Geo_Calc::Dis_PointToLine(pa.points[i],Line(pb.points[j],pb.points[(j+1)%pb.points.size()]));
        //printf("%d %d %f\n",i,j,dis);
        if(dis < 0.1)
        {
            Deal(this, a,b, pb.points[j] - pb.points[(j+1)%pb.points.size()] );
            return 1;
        }
    }


    return 0;
}
void SandBox::DealWithCollision( void DealBW(SandBox *box, int a,int b, Point dir), void DealBB(SandBox *box, int a,int b, Point dir) )
{
    const std::set<int> *bset = balls.GetIndex();
    const std::set<int> *wset = walls.GetIndex();
    int i,j;
    Point tv1,tv2;
    //Check Balls and Walls
    for(std::set<int>::iterator ii=bset->begin(); ii!=bset->end(); ii++)
    {
        i = *ii;
        //tv1 = Geo_Calc::Zero(balls[i].v);
        //tv1 = Point();
        //balls[i].real_shape = balls[i].real_shape + tv1;
        for(std::set<int>::iterator jj=wset->begin();jj!=wset->end();jj++)
        {

            j = *jj;
            isCollision(i, j, balls[i].real_shape, walls[j].shape, SandBox::DefaultDealBW);
        }
        //balls[i].real_shape = balls[i].real_shape - tv1;
    }

    //Check Balls and Balls
    for(std::set<int>::iterator ii=bset->begin(); ii!=bset->end(); ii++)
    {
        i = *ii;
        //balls[i].real_shape = balls[i].real_shape + balls[i].v*1e-7;
        for(std::set<int>::iterator jj=ii; jj!=bset->end(); jj++)
        if(ii!=jj){
            //balls[j].real_shape = balls[j].real_shape + balls[j].v*1e-7;

            j = *jj;
            if (! isCollision(i, j, balls[i].real_shape, balls[j].real_shape, SandBox::DefaultDealBB) )
            isCollision(j, i, balls[j].real_shape, balls[i].real_shape, SandBox::DefaultDealBB);

            //balls[j].real_shape = balls[j].real_shape - balls[j].v*1e-7;
        }
        //balls[i].real_shape = balls[i].real_shape - balls[i].v*1e-7;
    }
}
}
