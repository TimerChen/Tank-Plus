#include "SandBox.h"
#include "Geo_Calc.h"
#include <Ball_Polygon.h>
namespace GAME
{
//Public Functions
SandBox::SandBox()
{
    //num_balls = num_walls = 0;
    Field_Force = Point();
    left_time = 1;
}
void SandBox::Refresh(short first)
{
    //Reset left time
    if(first)
        left_time = 1;

    //Add Field_Force
    const std::set<int> *fset = forces.GetIndex();
    for(std::set<int>::iterator ii = fset->begin();ii!=fset->end();ii++)
    {
        int i = *ii;
        forces[i] = Field_Force;
    }
    //Add forces
    const std::set<int> *rfset=raw_forces.GetIndex();

    for( std::set<int>::iterator ii=rfset->begin();ii!=rfset->end();ii++ )
    {
        if(first && raw_forces[*ii].life == 0)
        {
            DeleteForces(*ii);
            continue;
        }

        int id = raw_forces[*ii].aim;
        forces[id] = forces[id] + raw_forces[*ii].v;
        if(first)
            raw_forces[*ii].life-=1;
    }

}
double SandBox::GetNextTime()
{
    //if at time l there is some collision

    //
    if (RunTimes == 59)
        RunTimes = 59;
    double l,r;
    HashCode status1,status2;
    IMvector<Ball_Polygon> tmp_balls;

    l = 0;r = left_time;
    //printf("check l\n");
    tmp_balls = GetNextBalls(l);
    status1 = CollisionCheck( &tmp_balls );

    l = 0;r = left_time;
    //printf("check l\n");
    tmp_balls = GetNextBalls(l);
    status1 = CollisionCheck( &tmp_balls );

    //想做得更精细可以暴力从中间挑几个时间check一下
    //printf("check r\n");
    double step = 0.1;
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
    printf("Collision!\n");
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
    if(balls[0].pos.y!=balls[1].pos.y)
        balls[0].pos.y = balls[1].pos.y;
    //...
    DealWithCollision( DealBW, DealBB );
    left_time -= t;
    return 1;
}
int SandBox::AddForce( Force f )
{
    int id;
    id = raw_forces.insert(f);
    return id;
}
int SandBox::AddBall( Ball_Polygon ball )
{
    int id;
    id = balls.insert(ball);
    forces.insert(Point());
    tracing.insert(-1);
    return id;
}
int SandBox::AddWall( Wall wall )
{
    int id;
    id = walls.insert(wall);
    forces.insert(Point());
    return id;
}
bool SandBox::DeleteForces( int id )
{
    if(!raw_forces.erase(id)) return 0;
    return 1;
}
bool SandBox::DeleteBall( int id )
{
    if(!balls.erase(id))return 0;
    tracing.erase(id);
    //clear old forces.
    const std::set<int> *rfset=raw_forces.GetIndex();
    for(std::set<int>::iterator i=rfset->begin();i!=rfset->end();i++)
    if(raw_forces[*i].aim == id)
        raw_forces.erase(*i);
    return 1;
}
bool SandBox::DeleteWall( int id )
{
    if(!walls.erase(id)) return 0;
    return 1;
}
void SandBox::AddTracing( int id, int aim, short type )
{
    tracing[id]=aim;
    if(type)
    {
        balls[aim].pos = balls[aim].pos-balls[id].pos;
        balls[aim].GetRealShape();
        balls[aim].shape = balls[aim].real_shape;
        balls[aim].rotate_rangle = 0;
        balls[aim].pos = balls[id].pos;
    }
}
void SandBox::ClearTracing( int id )
{
    tracing[id]=-1;
}
void SandBox::DefaultDealBW( SandBox *box, int a, int b, Point dir )
{

    dir = Geo_Calc::Zero(dir);
    dir = Geo_Calc::Normal(dir);

    //box->balls[a].rotate_v = 0;
    Point tv;
    double len1;
    //printf("(%f, %f)",dir.x,dir.y);
    printf("(%f, %f)\n",box->balls[a].v.x,box->balls[a].v.y);
    len1 = Geo_Calc::Dot( box->balls[a].v, dir );
    tv = dir * len1;
    //printf("(%f, %f)",dir.x,dir.y);
    box->balls[a].v = box->balls[a].v - tv;


    len1*=1;
    tv = dir * len1;//ratio?

    const double MLEN = 1.5;

    if(fabs(len1) <= MLEN && len1!=0)
    {
        printf("fuckyou!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        tv = tv *(MLEN/fabs(len1));


    }

    box->balls[a].v = box->balls[a].v - tv;
}
void SandBox::DefaultDealBB( SandBox *box, int a, int b, Point dir )
{
    dir = Geo_Calc::Zero(dir);
    dir = Geo_Calc::Normal(dir);

    box->balls[a].rotate_v *= 0.4;
    box->balls[b].rotate_v *= 0.4;
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

    v11 *= 1;//ratio?
    v22 *= 1;//ratio?

    const double MLEN = 1.5;
    if(fabs(v11) <= MLEN && v11!=0) v11 = v11 *(MLEN/fabs(v11));
    if(fabs(v22) <= MLEN && v22!=0) v22 = v22 *(MLEN/fabs(v22));

    box->balls[a].v = box->balls[a].v + dir * v11;
    box->balls[b].v = box->balls[b].v + dir * v22;
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
    }
    //trace on!
    for(std::set<int>::iterator ii = set_ball->begin();ii!=set_ball->end();ii++)
    if(tracing[*ii]!=-1)
    {
        int i = *ii,j = tracing[*ii];
        tb = reballs[i];
        tb.cent = reballs[j].cent;
        //tb.v = balls[j].v;
        //tb.rotate_v = balls[j].rotate_v;
        tb.pos = reballs[j].pos;
        tb.rotate_rangle = reballs[j].rotate_rangle;
        tb.GetRealShape();
        reballs[i] = tb;
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
        {
            hc = hc + ( std::to_string(i) + std::to_string(j) );
            printf("Ball%d and Wall%d Collision!\n",i,j);
        }

    }
    hc = hc + std::string("#");
    //Check Balls and Balls
    for(std::set<int>::iterator ii=bset->begin(); ii!=bset->end(); ii++)
    for(std::set<int>::iterator jj=ii; jj!=bset->end(); jj++)
    if(ii!=jj){
        i = *ii;
        j = *jj;
        if( Geo_Calc::CheckKick_PolygonToPolygon( (*b)[i].real_shape, (*b)[j].real_shape, 1 ) )
        {
            hc = hc + ( std::to_string(i) + std::to_string(j) );
            printf("Ball%d and Ball%d Collision!\n",i,j);
        }

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
        if(dis < eps*100)
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
            if(! isCollision(i, j, balls[i].real_shape, walls[j].shape, SandBox::DefaultDealBW) )
                isCollision(i, j, walls[j].shape, balls[i].real_shape, SandBox::DefaultDealBW);
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
